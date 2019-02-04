
#ifndef __MATH3D_H__
#define __MATH3D_H__

typedef float matrix[9];
typedef float3 vector;


//=============================Basic Math=============================

static float
lerp(const float a,const float b,float value)
{
    //return linear interpolation between the value a and b
    private float result = a*(1-value)+b*value;
    return result;
}

static float3
lerpv(const float3 a,const float3 b,float value)
{
    //return linear interpolation between the vector a and b
    private float3 result = a*(1-value)+b*value;
    return result;
}


static float
fit(float a,const float smin,const float smax,const float min,const float max)
{
    //takes the value in the range (smin.smax) and shifts it to the corresponding value in the new range (min,max)
    private float slen = smax-smin;
    private float len = max-min;
    a -= smin;
    a /= slen;
    a *= len;
    a += min;
    return a;
}

static float
fit01(float a,const float min,const float max)
{
    //takes the value in the range (0,1) and shifts it to the corresponding value in the new range (min,max)
    private float len = max-min;
    a *= len;
    a += min;
    return a;
}

static float3
fitv(float3 a,const float3 smin,const float3 smax,const float3 min,const float3 max)
{
    //takes the vector in range (smin.smax) and shifts it to the corresponding value in the new range (min,max)
    a.x = fit(a.x,smin.x,smax.x,min.x,max.x);
    a.y = fit(a.y,smin.y,smax.y,min.y,max.y);
    a.z = fit(a.z,smin.z,smax.z,min.z,max.z);
    return a;
}

static float
angle(float3 v1,float3 v2)
{
    //computes the angle between vector v1 and v2
    v1 = normalize(v1);
    v2 = normalize(v2);
    private float angle = acos(dot(v1,v2));
    angle = degrees(angle);
    return angle;
}



//=============================Quaternion=============================

static float4
qnormalize(float4 q)
{
    //normalizes quaternion
    private const float mag2 = q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w;
    if(mag2 == 0.0f) return q;
    private const float mag = sqrt(mag2);
    q.x /= mag;
    q.y /= mag;
    q.z /= mag;
    q.w /= mag;

    return q;
}

static float3
qrotate(const float3 v,const float4 q)
{
    //rotates vector by quaternion
    private const float3 quat_vector = {q.x, q.y, q.z};
    private const float quat_scalar = q.w;
    
    private const float3 t = 2.0f * cross(quat_vector, v);
    private float3 rotated_vector = v + (quat_scalar * t) + cross(quat_vector, t);
    
    return rotated_vector;
}


static float4
dihedral(const float3 v1,const float3 v2)
{
    //computes the rotation quaternion which rotates the vector v1 onto the vector v2
    private float3 v = cross(v1, v2);
    private float  v1_len = length(v1);
    private float  v2_len = length(v2);
    
    private float q_w = sqrt(v1_len * v1_len * v2_len * v2_len) + dot(v1, v2);
    
    private float4 q = {v.x, v.y, v.z, q_w};
    
    q = normalize(q);
    return q;
}

static float4
eulertoq(const float3 v)
{
    //creates a quaternion from euler angles
    private float4 q;
    private const float x = v.x*0.5f;
    private const float y = v.y*0.5f;
    private const float z = v.z*0.5f;
    private const float sx = sin(x);
    private const float sy = sin(y);
    private const float sz = sin(z);
    private const float cx = cos(x);
    private const float cy = cos(y);
    private const float cz = cos(z);
    q.x = sx*cy*cz - cx*sy*sz;
    q.y = cx*sy*cz + sx*cy*sz;
    q.z = cx*cy*sz - sx*sy*cz;
    q.w = cx*cy*cz + sx*sy*sz;

    return q;
}

static float3
qtoeuler(const float4 q)
{
    //creates euler angle representing quaternion
    private float3 v;
    v.x = atan2(2.0f*(q.x*q.w),1.0f-2.0f*(q.x*q.x+q.y*q.y));
    v.y = asin(2.0f*(q.y*q.w-q.x*q.z));
    v.z = atan2(2.0f*(q.z*q.w+q.x*q.y),1.0f-2.0f*(q.y*q.y+q.z*q.z));
    return v;
}

static float4
quaternion(const float ang,float3 axi)
{
    //generates a quaternion using angle and axi
    axi = normalize(axi);
    private float4 q;
    const float sinAng = sin(ang*0.5f);
    
    q.x = axi.x*sinAng;
    q.y = axi.y*sinAng;
    q.z = axi.z*sinAng;
    q.w = cos(ang*0.5f);

    return q;
}

static void
qconvert(matrix a,const float4 q)
{
    //converts a quaternion to a 3x3matrix
    private const float x2 = q.x*q.x;
    private const float y2 = q.y*q.y;
    private const float z2 = q.z*q.z;
    private const float xy = q.x*q.y;
    private const float xz = q.x*q.z;
    private const float yz = q.y*q.z;
    private const float wx = q.w*q.x;
    private const float wy = q.w*q.y;
    private const float wz = q.w*q.z;

    a[0] = 1.0f - 2.0f * (y2 + z2);
    a[1] = 2.0f * (xy + wz);
    a[2] = 2.0f * (xz - wy);
    a[3] = 2.0f * (xy - wz);
    a[4] = 1.0f - 2.0f * (x2 + z2);
    a[5] = 2.0f * (yz + wx);
    a[6] = 2.0f * (xz + wy);
    a[7] = 2.0f * (yz - wx);
    a[8] = 1.0f - 2.0f * (x2 + y2);
}

static float4
qMul(const float4 q1,const float4 q2)
{
    //multiplies two quaternions and returns the result
    private float4 q;
    q.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
    q.y = q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z;
    q.z = q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x;
    q.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    return q;
}


static float4
qinvert(float4 q)
{
    //inverts a quaternion rotation
    q.x *= -1.0;
    q.y *= -1.0;
    q.z *= -1.0;
    return q;
}

static float4
qlerp(const float4 q1,const float4 q2,const float value)
{
    //return linear interpolation between the q1 and q2
    private float4 q;
    q.x = lerp(q1.x,q2.x,value);
    q.y = lerp(q1.y,q2.y,value);
    q.z = lerp(q1.z,q2.z,value);
    q.w = lerp(q1.w,q2.w,value);
    q = qnormalize(q);

    return q;
}

static float4
qslerp(const float4 q1,const float4 q2,const float value)
{
    //return a quaternion blend between q1 and q2 based on the bias
    private float4 q;

    private float cosa = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
    
    // If the dot product is negative, the quaternions have opposite handed-ness and slerp won't take
    // the shorter path. Fix by reversing one quaternion.
    if ( cosa < 0.0f ) 
    {
        q2.x = -q2.x;
        q2.y = -q2.y;
        q2.z = -q2.z;
        q2.w = -q2.w;
        cosa = -cosa;
    }
    
    private float k0, k1;
    
    // If the inputs are too close for comfort, linearly interpolate
    if ( cosa > 0.9995f ) 
    {
        k0 = 1.0f - value;
        k1 = value;
    }
    else 
    {
        float sina = sqrt( 1.0f - cosa*cosa );
        float a = atan2( sina, cosa );
        k0 = sin((1.0f - value)*a)  / sina;
        k1 = sin(value*a) / sina;
    }
    q.x = q1.x*k0 + q2.x*k1;
    q.y = q1.y*k0 + q2.y*k1;
    q.z = q1.z*k0 + q2.z*k1;
    q.w = q1.w*k0 + q2.w*k1;

    return q;
}


static void
qconvertToaa(float3 *axi,float *angle,const float4 q)
{
    //converts a quaternion to axi and angle
    //example: qconvertToaa(&axi,&angle,q)
    private const float scale = sqrt(q.x*q.x+q.y*q.y+q.z*q.z);
    axi->x = q.x/scale;
    axi->y = q.y/scale;
    axi->z = q.z/scale;
    *angle = acos(q.w)*2.0f;
}



//=============================Random=============================
static float
srand(const float x, const float y){
    //core random function
     private float a = cos(x * 12.9898f + y * 4.1414f) * 43758.5453f;
     return a-floor(a);
     
}

static float
rand(const float3 seed){
    //return random float
    private float a = srand(seed.x, seed.y);
    private float b = srand(seed.z, seed.y);
    private float c = srand(seed.x, seed.z);
    private float d = srand(a, b);
    private float e = srand(b, c);
    private float f = srand(d, e);

    return f;
}

static float3
randv(const float3 seed){
    //return random float3
    private float a = srand(seed.x, seed.y);
    private float b = srand(seed.z, seed.y);
    private float c = srand(seed.x, seed.z);
    private float d = srand(a, b);
    private float e = srand(b, c);
    private float f = srand(d, e);
    private float3 r = {d,e,f};
    return r;
}


//=============================Matrix=============================
static void
ident(matrix a)
{
    //makes matrix a become identity matrix
    for(int i=0;i<9;i++){
        a[i] = 0;
    }
    a[0] = 1;
    a[4] = 1;
    a[8] = 1;
}

static void
mCopy(matrix a,const matrix b)
{
    //copies matrix b to a
    for(int i=0;i<9;i++){
        a[i] = b[i];
    }
}

static void 
mstore(const matrix a,const int idx, global float * data)
{
    //stores matrix to attribute
    private const int start = idx*9;
    private int id = 0;
    for(int i = start;i<start+9;i++){
        data[i] = a[id];
        id++;
    }
}

static void 
mload(matrix a,const int idx, global float * data)
{
    //loads matix from attribute
    private const int start = idx*9;
    private int id = 0;
    for(int i = start;i<start+9;i++){
        a[id] = data[i];
        id++;
    }
}

static void
mMul(matrix a,matrix b,const matrix c)
{
    //multiplies matrix b,c and apply the result to matrix a
    private matrix tmp;
    private int n = 0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            n = i*3;
            tmp[n+j] = b[n]*c[j] + b[n+1]*c[j+3] + b[n+2]*c[j+6];
        }
    }
    mCopy(a,tmp);
}



static float3
vmMul(float3 a,const matrix b)
{
    //vector multiply matrix
    private float3 tmp;
    tmp.x = a.x*b[0] + a.y*b[3] + a.z*b[6];
    tmp.y = a.x*b[1] + a.y*b[4] + a.z*b[7];
    tmp.z = a.x*b[2] + a.y*b[5] + a.z*b[8];
    return tmp;
}


static void
mScale(matrix a,const float3 b)
{
    //scales the matrix a in three directions simultaneously (X, Y, Z - given by the components of the scale_vector).
    a[0] *= b.x;
    a[4] *= b.y;
    a[8] *= b.z;
}

static void
mDirScale(matrix a,const float3 d,float k)
{
    //scales the mateix a ,d is scaled direction,k is strength
    k -= 1.0f;
    private matrix rot;
    rot[0] = 1 + k * d.x*d.x;
    rot[1] = k * d.x*d.y;
    rot[2] = k * d.x*d.z;
    rot[3] = k * d.x*d.y;
    rot[4] = 1 + k * d.y*d.y;
    rot[5] = k * d.y*d.z;
    rot[6] = k * d.x*d.z;
    rot[7] = k * d.y*d.z;
    rot[8] = 1 + k * d.z*d.z;
    mMul(a,a,rot);
}

#endif
