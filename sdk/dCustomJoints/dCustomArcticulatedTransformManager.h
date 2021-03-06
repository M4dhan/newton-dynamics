/* Copyright (c) <2003-2016> <Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely
*/


//////////////////////////////////////////////////////////////////////

#ifndef D_CUSTOM_ARTICULATED_TRANSFORM_MANAGER_H_
#define D_CUSTOM_ARTICULATED_TRANSFORM_MANAGER_H_

#include "dCustomJointLibraryStdAfx.h"
#include "dCustomControllerManager.h"

//#define D_HIERACHICAL_CONTROLLER_MAX_BONES	64

#define HIERACHICAL_ARTICULATED_PLUGIN_NAME	"__articulatedTransformManager__"

// a Skeleton Transform controller is use to calculate local transform on contractions of rigid bodies and joint that form part of a hierarchical Skeleton
class dCustomArticulatedTransformController: public dCustomControllerBase
{
	public:
	class dSkeletonBone: public dList<dSkeletonBone>
	{
		public: 
		dMatrix m_bindMatrix;
		NewtonBody* m_body;
		dSkeletonBone* m_parent;
		dCustomArticulatedTransformController* m_controller;

		dCustomJoint* FindJoint() const; 
	};

	CUSTOM_JOINTS_API dCustomArticulatedTransformController();
	CUSTOM_JOINTS_API ~dCustomArticulatedTransformController();

	CUSTOM_JOINTS_API dSkeletonBone* GetRoot () const;
	CUSTOM_JOINTS_API dSkeletonBone* AddRoot (NewtonBody* const bone, const dMatrix& bindMatrix);
	CUSTOM_JOINTS_API dSkeletonBone* AddBone (NewtonBody* const bone, const dMatrix& bindMatrix, dSkeletonBone* const parentBone);

	void SetCalculateLocalTransforms (bool val) {m_calculateLocalTransform = val;}
	bool GetCalculateLocalTransforms () const {return m_calculateLocalTransform;}
	
	protected:
	CUSTOM_JOINTS_API void Init ();
	CUSTOM_JOINTS_API virtual void PreUpdate(dFloat timestep, int threadIndex);
	CUSTOM_JOINTS_API virtual void PostUpdate(dFloat timestep, int threadIndex);
	
	private:
	dList<dSkeletonBone> m_bones;
	void* m_collisionAggregate;
	bool m_calculateLocalTransform;
	friend class dCustomArticulaledTransformManager;
};

class dCustomArticulaledTransformManager: public dCustomControllerManager<dCustomArticulatedTransformController> 
{
	public:
	CUSTOM_JOINTS_API dCustomArticulaledTransformManager(NewtonWorld* const world, const char* const name = HIERACHICAL_ARTICULATED_PLUGIN_NAME);
	CUSTOM_JOINTS_API virtual ~dCustomArticulaledTransformManager();

	CUSTOM_JOINTS_API virtual dCustomArticulatedTransformController* CreateTransformController ();

	CUSTOM_JOINTS_API virtual void OnDebug(dCustomJoint::dDebugDisplay* const debugContext) = 0;
	CUSTOM_JOINTS_API virtual void OnPreUpdate (dCustomArticulatedTransformController* const controller, dFloat timestep, int threadIndex) const = 0;
	CUSTOM_JOINTS_API virtual void OnUpdateTransform (const dCustomArticulatedTransformController::dSkeletonBone* const bone, const dMatrix& localMatrix) const = 0;

	private: 
	friend class dCustomArticulatedTransformController;
};


#endif 

