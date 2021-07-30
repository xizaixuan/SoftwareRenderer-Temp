#include "gltf-loader.h"

#include <iostream>
#include <memory>  // c++11
#include "../Framework/Mesh.h"
#include "tiny_gltf.h"
#include "../Mathematics/Float3.h"
#include "../Framework/Texture.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION

static std::string GetFilePathExtension(const std::string &FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	return "";
}

///
/// Loads glTF 2.0 mesh
///
bool LoadGLTF(const std::string &filename, std::vector<Mesh> *meshes, std::vector<Texture> *textures, std::vector<Material> *materials)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
    const std::string ext = GetFilePathExtension(filename);

    bool ret = false;
    if (ext.compare("glb") == 0) {
        // assume binary glTF.
        ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename.c_str());
    }
    else
    {
        // assume ascii glTF.
        ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename.c_str());
    }

    if (!warn.empty())
    {
        std::cout << "glTF parse warning: " << warn << std::endl;
    }

    if (!err.empty())
    {
        std::cerr << "glTF parse error: " << err << std::endl;
    }
    
    if (!ret)
    {
        std::cerr << "Failed to load glTF: " << filename << std::endl;
        return false;
    }

    // Iterate through all the meshes in the glTF file
    for (const auto &gltfMesh : model.meshes)
    {
        // Create a mesh object
        Mesh loadedMesh(sizeof(float) * 3);

        // To store the min and max of the buffer (as 3D vector of floats)
        v3f pMin = {}, pMax = {};

        // Store the name of the glTF mesh (if defined)
        loadedMesh.name = gltfMesh.name;

        // For each primitive
        for (const auto &meshPrimitive : gltfMesh.primitives)
        {
            bool convertedToTriangleList = false;

            std::unique_ptr<intArrayBase> indicesArrayPtr = nullptr;
            {
                const auto &indicesAccessor = model.accessors[meshPrimitive.indices];
				const auto& bufferView = model.bufferViews[indicesAccessor.bufferView];
				const auto& buffer = model.buffers[bufferView.buffer];
				const auto dataAddress = buffer.data.data() + bufferView.byteOffset +
					indicesAccessor.byteOffset;
				const auto byteStride = indicesAccessor.ByteStride(bufferView);
				const auto count = indicesAccessor.count;

                // Allocate the index array in the pointer-to-base declared in the
                // parent scope
                switch (indicesAccessor.componentType)
                {
                    case TINYGLTF_COMPONENT_TYPE_BYTE:
                        indicesArrayPtr = std::unique_ptr<intArray<char> >(
                        new intArray<char>(arrayAdapter<char>(
                            dataAddress, count, byteStride)));
                        break;
                     
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                        indicesArrayPtr = std::unique_ptr<intArray<unsigned char> >(
                        new intArray<unsigned char>(arrayAdapter<unsigned char>(
                            dataAddress, count, byteStride)));
                        break;

                    case TINYGLTF_COMPONENT_TYPE_SHORT:
                    indicesArrayPtr =
                        std::unique_ptr<intArray<short> >(new intArray<short>(
                            arrayAdapter<short>(dataAddress, count, byteStride)));
                    break;
                     
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                    indicesArrayPtr = std::unique_ptr<intArray<unsigned short> >(
                        new intArray<unsigned short>(arrayAdapter<unsigned short>(
                            dataAddress, count, byteStride)));
                    break;
                     
                    case TINYGLTF_COMPONENT_TYPE_INT:
                    indicesArrayPtr = std::unique_ptr<intArray<int> >(new intArray<int>(
                        arrayAdapter<int>(dataAddress, count, byteStride)));
                    break;
                     
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                    indicesArrayPtr = std::unique_ptr<intArray<unsigned int> >(
                        new intArray<unsigned int>(arrayAdapter<unsigned int>(
                            dataAddress, count, byteStride)));
                    break;
                    default:
                    break;
                }
            }
            const auto &indices = *indicesArrayPtr;

            if (indicesArrayPtr)
            {

			    for (size_t i(0); i < indicesArrayPtr->size(); ++i)
			    {
				    loadedMesh.indices.push_back(indices[i]);
			    }
            }

            switch (meshPrimitive.mode)
            {
                // We re-arrange the indices so that it describe a simple list of
                // triangles
                case TINYGLTF_MODE_TRIANGLE_FAN:
                {
					if (!convertedToTriangleList)
					{
						// This only has to be done once per primitive
						convertedToTriangleList = true;

						// We steal the guts of the vector
						auto triangleFan = std::move(loadedMesh.indices);
						loadedMesh.indices.clear();

						// Push back the indices that describe just one triangle one by one
						for (size_t i{ 2 }; i < triangleFan.size(); ++i)
						{
							loadedMesh.indices.push_back(triangleFan[0]);
							loadedMesh.indices.push_back(triangleFan[i - 1]);
							loadedMesh.indices.push_back(triangleFan[i]);
						}
					}
                }
                break;
                case TINYGLTF_MODE_TRIANGLE_STRIP:
                {
				    if (!convertedToTriangleList)
				    {
					    // This only has to be done once per primitive
					    convertedToTriangleList = true;

					    auto triangleStrip = std::move(loadedMesh.indices);
					    loadedMesh.indices.clear();

					    for (size_t i{ 2 }; i < triangleStrip.size(); ++i)
					    {
						    loadedMesh.indices.push_back(triangleStrip[i - 2]);
						    loadedMesh.indices.push_back(triangleStrip[i - 1]);
						    loadedMesh.indices.push_back(triangleStrip[i]);
					    }
				    }
                }
                break;
                case TINYGLTF_MODE_TRIANGLES:  // this is the simpliest case to handle
                {
                    for (const auto &attribute : meshPrimitive.attributes)
                    {
                        const auto attribAccessor = model.accessors[attribute.second];
                        const auto &bufferView = model.bufferViews[attribAccessor.bufferView];
                        const auto &buffer = model.buffers[bufferView.buffer];
                        const auto dataPtr = buffer.data.data() + bufferView.byteOffset + attribAccessor.byteOffset;
                        const auto byte_stride = attribAccessor.ByteStride(bufferView);
                        const auto count = attribAccessor.count;
                      
                        if (attribute.first == "POSITION")
                        {
                            // get the position min/max for computing the boundingbox
                            pMin.x = attribAccessor.minValues[0];
                            pMin.y = attribAccessor.minValues[1];
                            pMin.z = attribAccessor.minValues[2];
                            pMax.x = attribAccessor.maxValues[0];
                            pMax.y = attribAccessor.maxValues[1];
                            pMax.z = attribAccessor.maxValues[2];
                          
                            switch (attribAccessor.type)
                            {
                                case TINYGLTF_TYPE_VEC3:
                                {
                                    switch (attribAccessor.componentType)
                                    {
                                        case TINYGLTF_COMPONENT_TYPE_FLOAT:
                                        {
										    // 3D vector of float
										    v3fArray positions(arrayAdapter<v3f>(dataPtr, count, byte_stride));

										    for (size_t i{ 0 }; i < positions.size(); ++i)
										    {
											    const auto v = positions[i];
											    loadedMesh.vertices.push_back(float3(v.x, v.y, v.z));
										    }
                                        }
                                        break;
                                        case TINYGLTF_COMPONENT_TYPE_DOUBLE:
                                        {
                                            v3dArray positions(arrayAdapter<v3d>(dataPtr, count, byte_stride));
                                            for (size_t i{ 0 }; i < positions.size(); ++i)
                                            {
                                                const auto v = positions[i];
                                                loadedMesh.vertices.push_back(float3(v.x, v.y, v.z));
                                            }
							            }
                                        break;
						            default:
							            break;
						            }
                                }break;
                            }
                        }
                      
                        if (attribute.first == "NORMAL")
                        {
                            switch (attribAccessor.type)
                            { 
                                case TINYGLTF_TYPE_VEC3:
                                {
                                    switch (attribAccessor.componentType)
                                    {
                                        case TINYGLTF_COMPONENT_TYPE_FLOAT:
                                        {
                                            v3fArray normals( arrayAdapter<v3f>(dataPtr, count, byte_stride));

                                            // For each triangle :
                                            for (size_t i{0}; i < indices.size() / 3; ++i)
                                            {
                                                // get the i'th triange's indexes
                                                auto f0 = indices[3 * i + 0];
                                                auto f1 = indices[3 * i + 1];
                                                auto f2 = indices[3 * i + 2];
                                              
                                                // get the 3 normal vectors for that face
                                                v3f n0 = normals[f0];
                                                v3f n1 = normals[f1];
                                                v3f n2 = normals[f2];
                                              
                                                // Put them in the array in the correct order
                                                loadedMesh.normals.push_back(float3(n0.x, n0.y, n0.z));
                                                loadedMesh.normals.push_back(float3(n1.x, n1.y, n1.z));
                                                loadedMesh.normals.push_back(float3(n2.x, n2.y, n2.z));
                                            }
                                        }
                                        break;
                                      
                                        case TINYGLTF_COMPONENT_TYPE_DOUBLE:
                                        {
										    v3dArray normals(arrayAdapter<v3d>(dataPtr, count, byte_stride));

										    // For each triangle :
										    for (size_t i{ 0 }; i < indices.size() / 3; ++i)
										    {
											    // get the i'th triange's indexes
											    auto f0 = indices[3 * i + 0];
											    auto f1 = indices[3 * i + 1];
											    auto f2 = indices[3 * i + 2];

											    // get the 3 normal vectors for that face
											    v3d n0 = normals[f0];
											    v3d n1 = normals[f1];
											    v3d n2 = normals[f2];

											    // Put them in the array in the correct order
											    loadedMesh.normals.push_back(float3(n0.x, n0.y, n0.z));
											    loadedMesh.normals.push_back(float3(n1.x, n1.y, n1.z));
											    loadedMesh.normals.push_back(float3(n2.x, n2.y, n2.z));
										    }
                                        }
                                        break;
                                    }
                                }break;
                            }
                        }
                      
                        // Face varying comment on the normals is also true for the UVs
                        if (attribute.first == "TEXCOORD_0")
                        {
                            switch (attribAccessor.type)
                            {
                                case TINYGLTF_TYPE_VEC2:
                                {
                                    switch (attribAccessor.componentType)
                                    {
                                        case TINYGLTF_COMPONENT_TYPE_FLOAT:
                                        {
                                            v2fArray uvs(arrayAdapter<v2f>(dataPtr, count, byte_stride));
                                          
                                            for (size_t i{0}; i < indices.size() / 3; ++i)
                                            {
                                                // get the i'th triange's indexes
                                                auto f0 = indices[3 * i + 0];
                                                auto f1 = indices[3 * i + 1];
                                                auto f2 = indices[3 * i + 2];

                                                // get the texture coordinates for each triangle's
                                                // vertices
                                                auto uv0 = uvs[f0];
                                                auto uv1 = uvs[f1];
                                                auto uv2 = uvs[f2];
                                              
                                                // push them in order into the mesh data
                                                loadedMesh.uvs.push_back(float2(uv0.x, uv0.y));
                                                loadedMesh.uvs.push_back(float2(uv1.x, uv1.y));
                                                loadedMesh.uvs.push_back(float2(uv2.x, uv2.y));
                                            }
                                        }
                                        break;
                                        case TINYGLTF_COMPONENT_TYPE_DOUBLE:
                                        {
										    v2fArray uvs(arrayAdapter<v2f>(dataPtr, count, byte_stride));

										    for (size_t i{ 0 }; i < indices.size() / 3; ++i)
										    {
											    // get the i'th triange's indexes
											    auto f0 = indices[3 * i + 0];
											    auto f1 = indices[3 * i + 1];
											    auto f2 = indices[3 * i + 2];

											    // get the texture coordinates for each triangle's
											    // vertices
											    auto uv0 = uvs[f0];
											    auto uv1 = uvs[f1];
											    auto uv2 = uvs[f2];

											    // push them in order into the mesh data
											    loadedMesh.uvs.push_back(float2(uv0.x, uv0.y));
											    loadedMesh.uvs.push_back(float2(uv1.x, uv1.y));
											    loadedMesh.uvs.push_back(float2(uv2.x, uv2.y));
                                            }
                                        }
                                        break;
                                    }
                                }
                                break;
                            } 
                        }
                    }
                }
                break;

                // These aren't triangles:

                case TINYGLTF_MODE_POINTS:
                case TINYGLTF_MODE_LINE:
                case TINYGLTF_MODE_LINE_LOOP:
                    break;
            }

            loadedMesh.material_ids.push_back(meshPrimitive.material);
        }

        // bbox :
        float3 bCenter(0,0,0);
        bCenter.x = 0.5f * (pMax.x - pMin.x) + pMin.x;
        bCenter.y = 0.5f * (pMax.y - pMin.y) + pMin.y;
        bCenter.z = 0.5f * (pMax.z - pMin.z) + pMin.z;

        for (size_t v = 0; v < loadedMesh.vertices.size(); v++)
        {
            loadedMesh.vertices[v] = loadedMesh.vertices[v] - bCenter;
        }

        loadedMesh.pivotXform.r0 = float4(1.0f, 0.0f, 0.0f, 0.0f);
        loadedMesh.pivotXform.r1 = float4(0.0f, 1.0f, 0.0f, 0.0f);
        loadedMesh.pivotXform.r2 = float4(0.0f, 0.0f, 1.0f, 0.0f);
        loadedMesh.pivotXform.r3 = float4(bCenter.x, bCenter.y, bCenter.z, 1.0f);

        meshes->push_back(loadedMesh);
        ret = true;
    }

	// Iterate through all texture declaration in glTF file
	for (const auto& gltfTexture : model.textures)
    {
		Texture loadedTexture;
		const auto& image = model.images[gltfTexture.source];
		loadedTexture.components = image.component;
		loadedTexture.width = image.width;
		loadedTexture.height = image.height;

		const auto size =
			image.component * image.width * image.height * sizeof(unsigned char);
		loadedTexture.image = new unsigned char[size];
		memcpy(loadedTexture.image, image.image.data(), size);
		textures->push_back(loadedTexture);
	}

    for (const auto& gltfMaterial : model.materials)
    {
        Material material;
        material.baseColorTexture = gltfMaterial.pbrMetallicRoughness.baseColorTexture.index;
        materials->push_back(material); 
    }
    
    return ret;
}
