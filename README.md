# Houdini-OpenCL-lib
Some function about quaternion 3x3matrix  and random

## Created by ARNO

typedef float matrix[9];

typedef float3 vector;


# Basic-Math

### float lerp(float a,float b,float value)

{
    return linear interpolation between the value a and b
}



### float3 lerpv(float3 a,float3 b,float value)

{
    return linear interpolation between the vector a and b
}




### float fit(float a,float smin,float smax,float min,float max)

{
    takes the value in the range (smin.smax) and shifts it to the corresponding value in the new range (min,max)
}



### float fit01(float a,float min,float max)

{
    takes the value in the range (0,1) and shifts it to the corresponding value in the new range (min,max)
}



### float3 fitv(float3 a,float3 smin,float3 smax,float3 min,float3 max)

{
    takes the vector in range (smin.smax) and shifts it to the corresponding value in the new range (min,max)
}



### float angle(float3 v1,float3 v2)

{
    calculates the angle between vector v1 and v2
}




# Quaternion

### float4 qnormalize(float4 q)

{
    normalizes quaternion q
}



### float3 qrotate(float3 v,float4 q)

{
    rotates vector v by quaternion q
}



### float4 dihedral(float3 v1,float3 v2)

{
    computes the rotation quaternion which rotates the vector v1 onto the vector v2
}



### float4 eulertoq(float3 v)

{
    creates a quaternion from euler angles
}



### float3 qtoeuler(float4 q)

{
    creates euler angle representing quaternion
}



### float4 quaternion(float ang,float3 axi)

{
    generates a quaternion using angle and axi
}



### void qconvert(matrix &m,float4 q)

{
    converts a quaternion to a 3x3matrix
}



### float4 qMul(float4 q1,float4 q2)

{
    multiplies two quaternions and returns the result
}




### float4 qinvert(float4 q)

{
    inverts a quaternion rotation
}

### float4 qlerp(float4 q1,float4 q2,float value)

{
    return linear interpolation between the q1 and q2
}



### float4 qslerp(float4 q1,float4 q2,float value)

{
    return a quaternion blend between q1 and q2 based on the bias
}


### void qconvertToaa(float3 &axi,float &angle,float4 q)

{
    converts a quaternion to axi and angle
}




# Random

### float srand(float x,float y)

{
    core random function
}



### float rand(float3 seed)

{
    return random float
}



### float3  randv(float3 seed)

{
    return random vector
}




# Matrix

### void ident(matrix &a)

{
    makes matrix a become identity matrix
}



### void mCopy(matrix &a,const matrix b)

{
    copies matrix b to a
}



### void mstore(matrix a,int idx, global float * data)

{
    stores matrix to attribute
}



### void mload(matrix a,int idx, global float * data)

{
    loads matix from attribute
}



### void mMul(matrix &a,matrix b,matrix c)

{
    multiplies matrix b,c and apply the result to matrix a
}



### float3 vmMul(float3 a,matrix b)

{
    vector multiply matrix
}



### void mScale(matrix &a,float3 b)

{
    scales the matrix a in three directions simultaneously (X, Y, Z - given by the components of the scale_vector)
}



### void mDirScale(matrix &a,const float3 d,float k)

{
    scales the mateix a ,d is scaled direction,k is strength
}

 
