/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ά����
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float2_H_
#define _Float2_H_

#define  float2 Float2

class Float2
{
public:
	/// \brief �������캯��
	Float2(float x, float y);

	/// \brief ���ƹ��캯��
	Float2(const Float2& a);

	/// \brief ��������
	~Float2();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Float2& operator= (const Float2& a);

	/// \brief ���ض�Ԫ"+"�����
	Float2 operator+ (const Float2& a) const;

	/// \brief ���ض�Ԫ"-"�����
	Float2 operator- (const Float2& a) const;

	/// \brief ���ض�Ԫ"*"����� �����
	Float2 operator* (float a) const;

	/// \brief ���ض�Ԫ"*"����� ������
	float operator* (const Float2& a) const;

public:
	float x;
	float y;
};

#endif


