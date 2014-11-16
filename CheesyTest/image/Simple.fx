//-----------------------------------------------------------------------------
// File: Simple.fx
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 mWorldViewProj;  // World * View * Projection transformation

//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Position		: POSITION;   // vertex position 

	float4 Normal		: NORMAL;	  // vertex normal
    float4 Diffuse		: COLOR0;     // vertex diffuse color
	float3 TexCoord0	: TEXCOORD0;  // vertex texture coordinate
};

//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // transformed vertex position (clip space) 
	float2 TexCoord0  : TEXCOORD;	// vertex texture coordinates
    float4 Diffuse    : COLOR0;     // vertex diffuse color
};



//-----------------------------------------------------------------------------
VS_OUTPUT mainVS( const VS_INPUT Input )
{
	VS_OUTPUT Output;
	
	// transform the vertex position into projection space. 
    Output.Position = mul( Input.Position, mWorldViewProj );
    
	// pass on the texture coordinate
	Output.TexCoord0 = Input.TexCoord0;

	// pas on the 
    Output.Diffuse = Input.Diffuse;
    
    return Output;
}





//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 Color : COLOR0;  // Pixel color    
};

//--------------------------------------------------------------------------------------
// samplers are basically textures. A sampler2D is basically a 2D texture. By default
// they are bound to textures on the API side in order (i.e first one listed is texture
// 0, second one texture 1. You can also be explicit, like this:
// sampler2D s_2D : register( s0 );

sampler2D s_FirstTexture;
sampler2D s_SecondTexture;

//--------------------------------------------------------------------------------------
// This shader outputs the pixel's color by modulating the texture's
//       color with diffuse material color
//--------------------------------------------------------------------------------------
PS_OUTPUT mainPS( VS_OUTPUT Input )
{
	// an instance of our output
	PS_OUTPUT Output;

	// Sample the 2D texture using the interpolated texture coordinates and multiply by
	// the interpolated diffuse color. 
	Output.Color = tex2D(s_FirstTexture, Input.TexCoord0) * Input.Diffuse;

	return Output;
}



