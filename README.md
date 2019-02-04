# Houdini-OpenCL-lib
Some function about quaternion 3x3matrix  and random

typedef float matrix[9];
typedef float3 vector;


#===================================BasicMath=======================================

float lerp(float a,float b,float value)

{
  //
}



float3 lerpv(float3 a,float3 b,float value)

{
    //
}




float fit(float a,float smin,float smax,float min,float max)

{
    //
}



float fit01(float a,float min,float max)

{
    //
}



float3 fitv(float3 a,float3 smin,float3 smax,float3 min,float3 max)

{
    //
}



float angle(float3 v1,float3 v2)

{
    //
}




#===================================Quaternion=====================

float4 qnormalize(float4 q)

{
    //normalize quaternion
}



float3 qrotate(float3 v,float4 q)

{
    //apply the quaternion to vector
}



float4 dihedral(float3 v1,float3 v2)

{
    //calaulate quaternion form two vector
}



float4 ulertoq(float3 v)

{
    //convert euler angle to quaternion
}



float3 toeuler(float4 q)

{
    //convert quaternion to euler angle
}



float4 uaternion(float ang,float3 axi)

{
    //create quaternion form angle and axi
}



void convert(matrix &,float4 q)

{
    //convert quaternion to matrix
}



float4 qMul(float4 q1,float4 q2)

{
    //multiply two quaternion
}




float4 qinvert(float4 q)

{
    //calculate the complex conjugate of quaternion
}

float4 qlerp(float4 q1,float4 q2,float value)

{
    //
}



float4 qslerp(float4 q1,float4 q2,float value)

{
    //
}


void qconvertToaa(float3 &axi,float &angle,float4 q)
{
    //convert quaternion to axi and angle

}




#===========================Random==================================

float srand(float x,float y)

{
    //core of random function 
}



float rand(float3 seed)

{
    //random float

}



float3  randv(float3 seed)

{
    //random float3
}




#=============================Matrix=======================================

void ident(matrix &a)

{
    //make matrix a become ident matrix
}



void mCopy(matrix &a,const matrix b)

{
    //copy mateix b to a
}



void mstore(matrix a,int idx, global float * data)

{
    //store matrix to attribute
}



void mload(matrix a,int idx, global float * data)

{
    //load matix from attribute
}



void mMul(matrix &a,matrix b,matrix c)

{
    //matrix b,c multiply and apply the result to a

}



float3 vmMul(float3 a,const matrix b)

{
    //vector mulyiply matrix
}



void mScale(matrix &a,float3 b)

{
    //scale the mateix
}



void mDirScale(matrix &a,const float3 d,float k)

{
    //create a scale matrix by the direction of float3 d
}

 
