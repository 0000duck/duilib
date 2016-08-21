#ifndef CurveObject_h__
#define CurveObject_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	CurveObject.h
// ������		: 	daviyang35@QQ.com
// ����ʱ��	:	2015-05-22 16:13:53
// ˵��			:	����
/////////////////////////////////////////////////////////////*/
#pragma once
class Point2D;

namespace DuiLib
{

	// 2D����
class UILIB_API Point2D
{
public:
	Point2D(float x,float y);
	Point2D(const Point2D& rhs);
	void Add(Point2D& other);
	Point2D Scale(float t);

	float x;
	float y;
};

// 2D���꼯��
class UILIB_API CCurveObject
{
	friend class BezierAlgorithm;
public:
	CCurveObject(void);
	~CCurveObject(void);

	void AddPoint(float x, float y);
	void Reset();

protected:
	Point2DVector m_vec;
};

}
#endif // CurveObject_h__
