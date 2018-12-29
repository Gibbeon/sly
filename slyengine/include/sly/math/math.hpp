template <typename T>
T Math::min(T lhs, T rhs) 
{
    return lhs < rhs ? lhs : rhs;
}

template <typename T>
T Math::max(T lhs, T rhs) 
{
    return lhs > rhs ? lhs : rhs;
}


float Math::sqrt_appx(float x) {
    return sqrt(x);
    // this is slower than the SSE sqrt
    /*
    #define SQRT_MAGIC_F 0x5f3759df 

        union // get bits for floating value
        {
            float x;
            int i;
        } u;
        u.x = x;
        u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0

        const float xux = x*u.x;

        return xux*(1.5f - .5f*xux*u.x);
    */
}

float Math::sqrt(float x) 
{
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}

float Math::rsqrt_appx(float x)
{
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
}

float Math::rsqrt(float x)
{
    float xrsqrt_est = rsqrt_appx(x);
    return xrsqrt_est*(1.5f - x*0.5f*xrsqrt_est*xrsqrt_est); // NR iteration
}
