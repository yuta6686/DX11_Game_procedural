

// 2D 疑似乱数
float random2(in float2 vec)
{
    return frac(sin(dot(vec.xy, float2(12.9898, 78.233))) * 4378.545);
}

// 2D -> 2D 疑似乱数
float2 random22(in float2 vec)
{
    vec = float2(dot(vec, float2(127.1, 311.7f)),
        dot(vec, float2(269.5, 183.3)));
    
    return frac(sin(vec) * (4378.545));
}

float3 random33(in float3 vec)
{
    vec = float3(dot(vec, float3(127.1, 311.7f, 243.342)),
        dot(vec, float3(269.5, 183.3, 124.43)),
        dot(vec, float3(522.3, 243.1, 532.4)));
    
    return frac(sin(vec) * (4378.545));
}

float Noise(in float2 texcood)
{
    return random2(texcood);
}

float3 Checkerboard(float2 texcoord, float3 colorA, float3 colorB)
{
    const float check = fmod(floor(texcoord.x) + floor(texcoord.y), 2);
    return lerp(colorA, colorB, check);
}

float voronoi2(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);
    
    float value = 1.0f;
    
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 offset = float2(x, y);
            float2 position;
            position = random22(ivec + offset);
            float dist = distance(position + offset, fvec);
            value = min(value, dist);
        }
    }
    return value;
}

float valueNoise(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);

    float a = random2(ivec + float2(0.0, 0.0));
    float b = random2(ivec + float2(1.0, 0.0));
    float c = random2(ivec + float2(0.0, 1.0));
    float d = random2(ivec + float2(1.0, 1.0));
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    return lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y);
}

float perlinNoise2(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);
    
    float a = dot(random22(ivec + float2(0.0, 0.0)) * 2.0 - 1.0, fvec - float2(0.0, 0.0));
    float b = dot(random22(ivec + float2(1.0, 0.0)) * 2.0 - 1.0, fvec - float2(1.0, 0.0));
    float c = dot(random22(ivec + float2(0.0, 1.0)) * 2.0 - 1.0, fvec - float2(0.0, 1.0));
    float d = dot(random22(ivec + float2(1.0, 1.0)) * 2.0 - 1.0, fvec - float2(1.0, 1.0));
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    return lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y);
}

// パーリンノイズ3D
float perlinNoise3(in float3 vec)
{
    float3 ivec = floor(vec);
    float3 fvec = frac(vec);

    float a = dot(random33(ivec + float3(0.0, 0.0, 0.0)) * 2.0 - 1.0, fvec - float3(0.0, 0.0, 0.0));
    float b = dot(random33(ivec + float3(1.0, 0.0, 0.0)) * 2.0 - 1.0, fvec - float3(1.0, 0.0, 0.0));
    float c = dot(random33(ivec + float3(0.0, 1.0, 0.0)) * 2.0 - 1.0, fvec - float3(0.0, 1.0, 0.0));
    float d = dot(random33(ivec + float3(1.0, 1.0, 0.0)) * 2.0 - 1.0, fvec - float3(1.0, 1.0, 0.0));
            
    float e = dot(random33(ivec + float3(0.0, 0.0, 1.0)) * 2.0 - 1.0, fvec - float3(0.0, 0.0, 1.0));
    float f = dot(random33(ivec + float3(1.0, 0.0, 1.0)) * 2.0 - 1.0, fvec - float3(1.0, 0.0, 1.0));
    float g = dot(random33(ivec + float3(0.0, 1.0, 1.0)) * 2.0 - 1.0, fvec - float3(0.0, 1.0, 1.0));
    float h = dot(random33(ivec + float3(1.0, 1.0, 1.0)) * 2.0 - 1.0, fvec - float3(1.0, 1.0, 1.0));
    
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    return lerp(lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y), lerp(lerp(e, f, fvec.x), lerp(g, h, fvec.x), fvec.y), fvec.z);

}


// フラクタルブラウンモーション
float fbm2(in float2 vec, int octave)
{
    float value = 0.0f;
    float amplitude = 1.0f;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * perlinNoise2(vec);
        vec *= 2.0f;
        amplitude *= 0.5f;

    }
    return value;
}

// フラクタルパーリンノイズ3D
float fbm3(in float3 vec, int octave)
{
    float value = 0.0f;
    float amplitude = 1.0f;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * perlinNoise3(vec);
        vec *= 2.0f;
        amplitude *= 0.5f;
    }

    return value;
}