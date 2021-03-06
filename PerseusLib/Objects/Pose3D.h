#pragma once

#include "..\Renderer\Primitives\Quaternion.h"
#include "..\Primitives\Vector3D.h"

using namespace PerseusLib::Primitives;
using namespace Renderer::Primitives;

namespace PerseusLib
{
	namespace Objects
	{
		class Pose3D
		{
		public:
			Quaternion *rotation;
			VECTOR3DA *translation;

			void SetFrom(float *pose, int poseSize) 
			{
				if (poseSize == 4) this->SetFrom(pose[0], pose[1], pose[2], pose[3], 0.0f, 0.0f);
				if (poseSize == 6) this->SetFrom(pose[0], pose[1], pose[2], pose[3], pose[4], pose[5]);
				if (poseSize == 7) this->SetFrom(pose[0], pose[1], pose[2], pose[3], pose[4], pose[5], pose[6]); 
			}

			void SetFrom(Pose3D *pose) { 
				this->translation->x = pose->translation->x;
				this->translation->y = pose->translation->y;
				this->translation->z = pose->translation->z;
				this->rotation->vector4d.x = pose->rotation->vector4d.x;
				this->rotation->vector4d.y = pose->rotation->vector4d.y;
				this->rotation->vector4d.z = pose->rotation->vector4d.z;
				this->rotation->vector4d.w = pose->rotation->vector4d.w;		
			}

			void SetFrom(VECTOR3DA* translation, Quaternion* rotation){
				this->rotation->Set(rotation);
				this->translation->x = translation->x;
				this->translation->y = translation->y;
				this->translation->z = translation->z;
			}

			void SetFrom(VFLOAT tX, VFLOAT tY, VFLOAT tZ, VFLOAT rX, VFLOAT rY, VFLOAT rZ) {
				this->translation->x = tX;
				this->translation->y = tY;
				this->translation->z = tZ;
				this->rotation->SetFromEuler(rX,rY,rZ);
			}	

			void SetFrom(VFLOAT tX, VFLOAT tY, VFLOAT tZ, VFLOAT rX, VFLOAT rY, VFLOAT rZ, VFLOAT rW) {
				this->translation->x = tX;
				this->translation->y = tY;
				this->translation->z = tZ;
				this->rotation->vector4d.x = rX;
				this->rotation->vector4d.y = rY;
				this->rotation->vector4d.z = rZ;
				this->rotation->vector4d.w = rW;
			}	

			void GetModelViewMatrix(float *returnMatrix)
			{
				VFLOAT matrixFromSource[16]; 
				rotation->GetMatrix(matrixFromSource);

				returnMatrix[0] = matrixFromSource[0];
				returnMatrix[1] = matrixFromSource[1];
				returnMatrix[2] = matrixFromSource[2];
				returnMatrix[3] = 0.0f;

				returnMatrix[4] = matrixFromSource[4];
				returnMatrix[5] = matrixFromSource[5];
				returnMatrix[6] = matrixFromSource[6];
				returnMatrix[7] = 0.0f;

				returnMatrix[8] = matrixFromSource[8];
				returnMatrix[9] = matrixFromSource[9];
				returnMatrix[10] = matrixFromSource[10];
				returnMatrix[11] = 0.0f;

				returnMatrix[12] = translation->x;
				returnMatrix[13] = translation->y;
				returnMatrix[14] = translation->z;
				returnMatrix[15] = 1.0f;

			}

			void CopyInto(Pose3D *targetPose) {
				targetPose->translation->x = this->translation->x;
				targetPose->translation->y = this->translation->y;
				targetPose->translation->z = this->translation->z;
				targetPose->rotation->vector4d.x = this->rotation->vector4d.x;
				targetPose->rotation->vector4d.y = this->rotation->vector4d.y;
				targetPose->rotation->vector4d.z = this->rotation->vector4d.z;
				targetPose->rotation->vector4d.w = this->rotation->vector4d.w;
			}

			void Clear()
			{
				this->translation->x = 0; this->translation->y = 0; this->translation->z = 0;
				this->rotation->vector4d.x = 0; this->rotation->vector4d.y = 0; this->rotation->vector4d.z = 0; this->rotation->vector4d.w = 0;
			}

			Pose3D(VFLOAT tX, VFLOAT tY, VFLOAT tZ, VFLOAT rX, VFLOAT rY, VFLOAT rZ) { 
				rotation = new Quaternion(); translation = new VECTOR3DA(); 
				this->SetFrom(tX, tY, tZ, rX, rY, rZ);
			}

			Pose3D(float *pose, int poseSize) { 
				rotation = new Quaternion(); translation = new VECTOR3DA(); 
				this->SetFrom(pose, poseSize);
			}

			Pose3D(void) { rotation = new Quaternion();  translation = new VECTOR3DA(); }
			~Pose3D(void) { if (rotation) delete rotation; if (translation) delete translation;  }
		};
	}
}