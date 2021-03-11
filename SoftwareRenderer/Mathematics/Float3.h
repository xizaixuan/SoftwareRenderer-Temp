/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ά����
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float3_H_
#define _Float3_H_

#define  float3 Float3

class Float3
{
public:
	/// \brief �������캯��
	Float3(float x, float y, float z);

	/// \brief ���ƹ��캯��
	Float3(const Float3& a);

	/// \brief ��������
	~Float3();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Float3& operator =(const Float3& a);

	/// \brief ���ض�Ԫ"+"�����
	Float3 operator +(const Float3& a) const;

	/// \brief ���ض�Ԫ"-"�����
	Float3 operator -(const Float3& a) const;

	/// \brief ���ض�Ԫ"*"����� �����
	Float3 operator *(float a) const;

	/// \brief ���ض�Ԫ"*"����� ������
	float operator *(const Float3& a) const;

public:
	float x;
	float y;
	float z;
};

#endif