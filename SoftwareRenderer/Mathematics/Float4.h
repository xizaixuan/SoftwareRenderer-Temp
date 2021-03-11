/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ά����
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float4_H_
#define _Float4_H_

#define  float4 Float4

class Float4
{
public:
	/// \brief �������캯��
	Float4(float x, float y, float z);

	/// \brief �������캯��
	Float4(float x, float y, float z, float w);

	/// \brief ���ƹ��캯��
	Float4(const Float4& a);

	/// \brief ��������
	~Float4();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Float4& operator = (const Float4& a);

	/// \brief ���ض�Ԫ"+"�����
	Float4 operator +(const Float4& a) const;

	/// \brief ���ض�Ԫ"-"�����
	Float4 operator -(const Float4& a) const;

	/// \brief ���ض�Ԫ"*"����� �����
	Float4 operator *(float a) const;

	/// \brief ���ض�Ԫ"*"����� ������
	float operator *(const Float4& a) const;

public:
	float x;
	float y;
	float z;
	float w;
};

#endif
