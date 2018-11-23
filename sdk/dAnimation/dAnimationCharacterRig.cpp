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

#include "dAnimationStdAfx.h"
#include "dAnimationRigHinge.h"
#include "dAnimationCharacterRig.h"
#include "dAnimationCharacterRigManager.h"

dAnimationCharacterRig::dAnimationCharacterRig ()
	:dCustomControllerBase()
	,dAnimationRigJoint(NULL)
	,m_solver()
{
	m_root = this;
}

dAnimationCharacterRig::~dAnimationCharacterRig ()
{
}

void dAnimationCharacterRig::Init(NewtonBody* const body)
{
	dCustomControllerBase::m_body = body;
	dAnimationRigJoint::Init(body);
}

void dAnimationCharacterRig::Debug(dCustomJoint::dDebugDisplay* const debugContext) const
{
	dAnimationRigJoint::Debug(debugContext);
}

void dAnimationCharacterRig::Finalize()
{
	m_solver.Finalize(this);
}

NewtonBody* dAnimationCharacterRig::GetNewtonBody() const 
{
	return dCustomControllerBase::GetBody();
}


void dAnimationCharacterRig::PreUpdate(dFloat timestep, int threadIndex)
{
//	NewtonImmediateModeConstraint descriptor;
//	dAnimationRigHinge* joint = (dAnimationRigHinge*) m_children.GetFirst()->GetInfo();
//	int xxx = NewtonUserJointSubmitImmediateModeConstraint(joint->dCustomHinge::GetJoint(), &descriptor, timestep);

	RigidBodyToStates();
	m_solver.Update(timestep);
}


void dAnimationCharacterRig::PostUpdate(dFloat timestep, int threadIndex)
{
//	m_vehicle->RigidBodyToStates();

//	dAssert(m_bones.GetCount() == 1);

	dAnimationCharacterRigManager* const manager = (dAnimationCharacterRigManager*)GetManager();

	UpdateLocalTransforms (manager);
}
