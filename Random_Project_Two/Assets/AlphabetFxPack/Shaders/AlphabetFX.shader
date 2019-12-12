// Made with Amplify Shader Editor
// Available at the Unity Asset Store - http://u3d.as/y3X 
Shader "AlphabetFX"
{
	Properties
	{
		_SurfaceColor("Surface Color", Color) = (1,1,1,0)
		_Outlines_Color("OUTLINES COLOR", Color) = (0.57603,1,0,0)
		_Outlines_Color_Opacity("OUTLINES OPACITY", Range(0 , 10)) = 2
		_Faces_Color("FACES COLOR", Color) = (0.01201493,0.4473053,0.8490566,0)
		_Faces_Color_Opacity("FACES OPACITY", Range(0 , 10)) = 0
		_DiffuseMap("DIFFUSE MAP", 2D) = "white" {}
	_AnimationMask("ANIMATION MASK", 2D) = "white" {}
	_ExtraRotationVariationSpeed("GEARS EXTRA ROTATION VARIATION ", Float) = 7
		_FacePourcentage("FACES PERCENTAGE", Range(0 , 1)) = 0.6
		_GearsOutlinesIntensity("GEARS OUTLINES INTENSITY", Range(0 , 10)) = 0
		_Outlines_Mask("OUTLINES MASK", 2D) = "white" {}
	_OutlineMaskSpeed("OUTLINES MASK SPEED", Float) = 0
		_FarDistanceMax("DISTANCE MAX", Range(0 , 5)) = 1
		[HideInInspector] _texcoord4("", 2D) = "white" {}
	[HideInInspector] _texcoord("", 2D) = "white" {}
	[HideInInspector] _texcoord2("", 2D) = "white" {}
	[HideInInspector] __dirty("", Int) = 1
	}

		SubShader
	{
		Tags{ "RenderType" = "Transparent"  "Queue" = "Geometry+0" "IgnoreProjector" = "True" "IsEmissive" = "true" }
		Cull Off
		Blend SrcAlpha OneMinusSrcAlpha

		CGINCLUDE
#include "UnityShaderVariables.cginc"
#include "UnityPBSLighting.cginc"
#include "Lighting.cginc"
#pragma target 3.0
		struct Input
	{
		float3 worldNormal;
		float2 uv4_texcoord4;
		float2 uv_texcoord;
		float4 vertexColor : COLOR;
		float2 uv2_texcoord2;
	};

	uniform float _ExtraRotationVariationSpeed;
	uniform sampler2D _AnimationMask;
	uniform float _FarDistanceMax;
	uniform sampler2D _DiffuseMap;
	uniform float4 _SurfaceColor;
	uniform float _Outlines_Color_Opacity;
	uniform float4 _Outlines_Color;
	uniform sampler2D _Outlines_Mask;
	uniform float _OutlineMaskSpeed;
	uniform float _GearsOutlinesIntensity;
	uniform float _FacePourcentage;
	uniform float _Faces_Color_Opacity;
	uniform float4 _Faces_Color;


	float3 RotateAroundAxis(float3 center, float3 original, float3 u, float angle)
	{
		original -= center;
		float C = cos(angle);
		float S = sin(angle);
		float t = 1 - C;
		float m00 = t * u.x * u.x + C;
		float m01 = t * u.x * u.y - S * u.z;
		float m02 = t * u.x * u.z + S * u.y;
		float m10 = t * u.x * u.y + S * u.z;
		float m11 = t * u.y * u.y + C;
		float m12 = t * u.y * u.z - S * u.x;
		float m20 = t * u.x * u.z - S * u.y;
		float m21 = t * u.y * u.z + S * u.x;
		float m22 = t * u.z * u.z + C;
		float3x3 finalMatrix = float3x3(m00, m01, m02, m10, m11, m12, m20, m21, m22);
		return mul(finalMatrix, original) + center;
	}


	void vertexDataFunc(inout appdata_full v, out Input o)
	{
		UNITY_INITIALIZE_OUTPUT(Input, o);
		float4 appendResult117 = (float4((v.color.r * 1.0) , v.color.g , v.color.b , 0.0));
		float clampResult127 = clamp(v.texcoord3.xy.x , 0.1 , 2.0);
		float4 appendResult161 = (float4(_SinTime.z , 0.0 , 0.0 , 0.0));
		float2 uv2_TexCoord159 = v.texcoord1.xy + appendResult161.xy;
		float4 tex2DNode243 = tex2Dlod(_AnimationMask, float4(uv2_TexCoord159, 0, 0.0));
		float4 temp_output_144_0 = (v.color * tex2DNode243.r);
		float temp_output_228_0 = (temp_output_144_0).b;
		float3 appendResult97 = (float3((v.texcoord1.xy.x * -1.0) , v.texcoord1.xy.y , v.texcoord2.xy.x));
		float3 ase_vertex3Pos = v.vertex.xyz;
		float3 rotatedValue102 = RotateAroundAxis((appendResult97 / float3(100,100,100)), ase_vertex3Pos, appendResult117.xyz, (((clampResult127 * _ExtraRotationVariationSpeed) * (temp_output_228_0 / 1.0)) + _SinTime.w));
		float temp_output_283_0 = (0.002 * _FarDistanceMax);
		float4 temp_cast_3 = (temp_output_283_0).xxxx;
		float4 clampResult162 = clamp((temp_output_144_0 * v.texcoord3.xy.x * temp_output_283_0) , float4(0,0,0,0) , temp_cast_3);
		v.vertex.xyz += (float4(((rotatedValue102 - ase_vertex3Pos) * v.texcoord2.xy.y) , 0.0) + clampResult162).rgb;
	}

	void surf(Input i , inout SurfaceOutputStandard o)
	{
		float3 ase_worldNormal = i.worldNormal;
		float4 appendResult171 = (float4(ase_worldNormal.x , ase_worldNormal.y , 0.0 , 0.0));
		float4 tex2DNode173 = tex2D(_DiffuseMap, ((appendResult171 * float4(0.5,0.5,0.5,0)) + float4(float2(0.5,0.5), 0.0 , 0.0)).xy);
		float2 temp_cast_2 = (_OutlineMaskSpeed).xx;
		float2 panner278 = (1.0 * _Time.y * temp_cast_2 + i.uv_texcoord);
		float4 temp_output_135_0 = (i.uv4_texcoord4.y * _Outlines_Color_Opacity * _Outlines_Color * tex2D(_Outlines_Mask, panner278).r);
		o.Albedo = ((tex2DNode173 + _SurfaceColor) + temp_output_135_0).rgb;
		float4 appendResult161 = (float4(_SinTime.z , 0.0 , 0.0 , 0.0));
		float2 uv2_TexCoord159 = i.uv2_texcoord2 + appendResult161.xy;
		float4 tex2DNode243 = tex2D(_AnimationMask, uv2_TexCoord159);
		float4 temp_output_144_0 = (i.vertexColor * tex2DNode243.r);
		float temp_output_228_0 = (temp_output_144_0).b;
		float temp_output_270_0 = ((1.0 - _FacePourcentage) * 25.0);
		float lerpResult217 = lerp((pow((1.0 - sin((i.uv_texcoord.x * 0.5))) , temp_output_270_0) - 0.0) , (pow((1.0 - sin((i.uv_texcoord.y * 0.5))) , temp_output_270_0) - 0.0) , tex2DNode243.r);
		float clampResult224 = clamp((lerpResult217 * 1.0) , 0.0 , 10.0);
		o.Emission = (((temp_output_135_0 * _GearsOutlinesIntensity) * temp_output_228_0 * i.uv4_texcoord4.x) + ((clampResult224 * _Faces_Color_Opacity) * _Faces_Color * temp_output_228_0 * i.uv4_texcoord4.x)).rgb;
		o.Alpha = 1;
	}

	ENDCG
		CGPROGRAM
#pragma surface surf Standard keepalpha fullforwardshadows exclude_path:deferred vertex:vertexDataFunc 

		ENDCG
		Pass
	{
		Name "ShadowCaster"
		Tags{ "LightMode" = "ShadowCaster" }
		ZWrite On
		CGPROGRAM
#pragma vertex vert
#pragma fragment frag
#pragma target 3.0
#pragma multi_compile_shadowcaster
#pragma multi_compile UNITY_PASS_SHADOWCASTER
#pragma skip_variants FOG_LINEAR FOG_EXP FOG_EXP2
#include "HLSLSupport.cginc"
#if ( SHADER_API_D3D11 || SHADER_API_GLCORE || SHADER_API_GLES3 || SHADER_API_METAL || SHADER_API_VULKAN )
#define CAN_SKIP_VPOS
#endif
#include "UnityCG.cginc"
#include "Lighting.cginc"
#include "UnityPBSLighting.cginc"
		struct v2f
	{
		V2F_SHADOW_CASTER;
		float4 customPack1 : TEXCOORD1;
		float2 customPack2 : TEXCOORD2;
		float3 worldPos : TEXCOORD3;
		float3 worldNormal : TEXCOORD4;
		half4 color : COLOR0;
		UNITY_VERTEX_INPUT_INSTANCE_ID
	};
	v2f vert(appdata_full v)
	{
		v2f o;
		UNITY_SETUP_INSTANCE_ID(v);
		UNITY_INITIALIZE_OUTPUT(v2f, o);
		UNITY_TRANSFER_INSTANCE_ID(v, o);
		Input customInputData;
		vertexDataFunc(v, customInputData);
		float3 worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;
		half3 worldNormal = UnityObjectToWorldNormal(v.normal);
		o.worldNormal = worldNormal;
		o.customPack1.xy = customInputData.uv4_texcoord4;
		o.customPack1.xy = v.texcoord3;
		o.customPack1.zw = customInputData.uv_texcoord;
		o.customPack1.zw = v.texcoord;
		o.customPack2.xy = customInputData.uv2_texcoord2;
		o.customPack2.xy = v.texcoord1;
		o.worldPos = worldPos;
		TRANSFER_SHADOW_CASTER_NORMALOFFSET(o)
			o.color = v.color;
		return o;
	}
	half4 frag(v2f IN
#if !defined( CAN_SKIP_VPOS )
		, UNITY_VPOS_TYPE vpos : VPOS
#endif
	) : SV_Target
	{
		UNITY_SETUP_INSTANCE_ID(IN);
	Input surfIN;
	UNITY_INITIALIZE_OUTPUT(Input, surfIN);
	surfIN.uv4_texcoord4 = IN.customPack1.xy;
	surfIN.uv_texcoord = IN.customPack1.zw;
	surfIN.uv2_texcoord2 = IN.customPack2.xy;
	float3 worldPos = IN.worldPos;
	half3 worldViewDir = normalize(UnityWorldSpaceViewDir(worldPos));
	surfIN.worldNormal = IN.worldNormal;
	surfIN.vertexColor = IN.color;
	SurfaceOutputStandard o;
	UNITY_INITIALIZE_OUTPUT(SurfaceOutputStandard, o)
		surf(surfIN, o);
#if defined( CAN_SKIP_VPOS )
	float2 vpos = IN.pos;
#endif
	SHADOW_CASTER_FRAGMENT(IN)
	}
		ENDCG
	}
	}
		Fallback "Diffuse"
		CustomEditor "AlphabetFXPack_GUI"
}
/*ASEBEGIN
Version=15500
7;29;1906;1004;-6564.269;4168.018;1.820553;True;True
Node;AmplifyShaderEditor.CommentaryNode;254;3109.329,-1502.2;Float;False;2113.214;552.8196;Comment;14;160;161;159;243;149;144;228;237;148;151;147;162;283;282;;1,1,1,1;0;0
Node;AmplifyShaderEditor.SinTimeNode;160;3122.64,-1449.116;Float;False;0;5;FLOAT4;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.CommentaryNode;253;2500.497,-2387.877;Float;False;3594.121;708.9419;Comment;22;201;205;204;207;206;209;208;225;212;213;216;215;214;222;217;221;224;229;230;263;270;272;;1,1,1,1;0;0
Node;AmplifyShaderEditor.DynamicAppendNode;161;3286.721,-1399.279;Float;False;FLOAT4;4;0;FLOAT;0;False;1;FLOAT;0;False;2;FLOAT;0;False;3;FLOAT;0;False;1;FLOAT4;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;201;2549.187,-2174.811;Float;False;0;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.TextureCoordinatesNode;159;3464.367,-1446.211;Float;False;1;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;205;3272.362,-1963.318;Float;True;2;2;0;FLOAT;0;False;1;FLOAT;0.5;False;1;FLOAT;0
Node;AmplifyShaderEditor.RangedFloatNode;225;3384.417,-2104.635;Float;False;Property;_FacePourcentage;Face Pourcentage;9;0;Create;True;0;0;False;0;0.6;1;0;1;0;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;204;3271.662,-2327.719;Float;True;2;2;0;FLOAT;0;False;1;FLOAT;0.5;False;1;FLOAT;0
Node;AmplifyShaderEditor.SamplerNode;243;3726.327,-1179.38;Float;True;Property;_AnimationMask;AnimationMask;7;0;Create;True;0;0;False;0;0fc8bf4d13e7b2c44872d87a42008190;0fc8bf4d13e7b2c44872d87a42008190;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.VertexColorNode;149;3825.375,-1393.228;Float;False;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.CommentaryNode;255;5247.556,-867.3469;Float;False;2925.3;1019.782;Comment;21;126;95;233;127;120;232;96;99;118;245;97;234;117;244;103;111;102;250;106;121;142;;1,1,1,1;0;0
Node;AmplifyShaderEditor.OneMinusNode;272;3721.362,-2102.159;Float;False;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SinOpNode;206;3603.557,-2337.877;Float;True;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;144;4040.865,-1299.958;Float;False;2;2;0;COLOR;0,0,0,0;False;1;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.SinOpNode;207;3604.057,-1977.676;Float;True;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.OneMinusNode;209;3811.857,-1977.976;Float;True;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;126;5319.64,-541.5067;Float;False;3;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.ComponentMaskNode;228;4198.785,-1452.2;Float;False;False;False;True;False;1;0;COLOR;0,0,0,0;False;1;FLOAT;0
Node;AmplifyShaderEditor.OneMinusNode;208;3819.557,-2337.678;Float;True;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;270;3925.459,-2100.858;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;25;False;1;FLOAT;0
Node;AmplifyShaderEditor.RangedFloatNode;216;4382.565,-2078.092;Float;False;Constant;_EdgeSubstraction;Edge Substraction;8;0;Create;True;0;0;False;0;0;0.1;0;0;0;1;FLOAT;0
Node;AmplifyShaderEditor.CommentaryNode;252;2152.305,-3951.889;Float;False;4707.937;1056.31;Comment;18;165;171;169;172;170;173;246;138;135;176;131;277;278;276;260;279;134;281;;1,1,1,1;0;0
Node;AmplifyShaderEditor.ClampOpNode;127;5610.694,-621.7626;Float;False;3;0;FLOAT;0;False;1;FLOAT;0.1;False;2;FLOAT;2;False;1;FLOAT;0
Node;AmplifyShaderEditor.RangedFloatNode;233;5455.822,-378.473;Float;False;Property;_ExtraRotationVariationSpeed;Extra Rotation Variation Speed;8;0;Create;True;0;0;False;0;7;9;0;0;0;1;FLOAT;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;95;5306.879,-172.2776;Float;False;1;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleDivideOpNode;237;4572.571,-1395.067;Float;False;2;0;FLOAT;0;False;1;FLOAT;1;False;1;FLOAT;0
Node;AmplifyShaderEditor.PowerNode;212;4119.558,-2306.877;Float;True;2;0;FLOAT;0;False;1;FLOAT;30;False;1;FLOAT;0
Node;AmplifyShaderEditor.PowerNode;213;4150.558,-2018.877;Float;True;2;0;FLOAT;0;False;1;FLOAT;30;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleSubtractOpNode;215;4626.915,-2010.128;Float;True;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleSubtractOpNode;214;4628.158,-2279.078;Float;True;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.WireNode;256;4892.48,-688.3073;Float;False;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;99;5572.648,-225.7336;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;-1;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;232;5779.9,-485.3907;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.WorldNormalVector;165;2202.305,-3769.851;Float;False;False;1;0;FLOAT3;0,0,1;False;4;FLOAT3;0;FLOAT;1;FLOAT;2;FLOAT;3
Node;AmplifyShaderEditor.VertexColorNode;120;5830.331,-817.3469;Float;False;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.TextureCoordinatesNode;277;4270.23,-3608.962;Float;False;0;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.RangedFloatNode;279;4341.308,-3345.205;Float;False;Property;_OutlineMaskSpeed;Outline Mask Speed;12;0;Create;True;0;0;False;0;0;0;0;0;0;1;FLOAT;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;96;5297.556,-3.564632;Float;False;2;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.LerpOp;217;5031.558,-2150.877;Float;False;3;0;FLOAT;0;False;1;FLOAT;0;False;2;FLOAT;0.5;False;1;FLOAT;0
Node;AmplifyShaderEditor.CommentaryNode;260;5501.46,-3378.97;Float;False;284;257;c;1;220;;1,1,1,1;0;0
Node;AmplifyShaderEditor.SinTimeNode;245;5966.364,-432.7646;Float;False;0;5;FLOAT4;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;118;6264.329,-812.3468;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;1;False;1;FLOAT;0
Node;AmplifyShaderEditor.DynamicAppendNode;171;2467.558,-3760.91;Float;False;FLOAT4;4;0;FLOAT;0;False;1;FLOAT;0;False;2;FLOAT;0;False;3;FLOAT;0;False;1;FLOAT4;0
Node;AmplifyShaderEditor.DynamicAppendNode;97;5731.455,-18.18366;Float;False;FLOAT3;4;0;FLOAT;0;False;1;FLOAT;0;False;2;FLOAT;0;False;3;FLOAT;0;False;1;FLOAT3;0
Node;AmplifyShaderEditor.PannerNode;278;4549.955,-3504.103;Float;False;3;0;FLOAT2;0,0;False;2;FLOAT2;1,0;False;1;FLOAT;1;False;1;FLOAT2;0
Node;AmplifyShaderEditor.RangedFloatNode;222;5139.934,-1989.493;Float;False;Constant;_GlowStrength;Glow Strength;6;0;Create;True;0;0;False;0;1;1;0;0;0;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;234;5943.624,-583.1987;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;221;5301.899,-2151.219;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.DynamicAppendNode;117;6449.485,-767.2748;Float;False;FLOAT4;4;0;FLOAT;0;False;1;FLOAT;0;False;2;FLOAT;0;False;3;FLOAT;0;False;1;FLOAT4;0
Node;AmplifyShaderEditor.SimpleAddOpNode;244;6174.051,-580.3066;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;1000;False;1;FLOAT;0
Node;AmplifyShaderEditor.RangedFloatNode;138;5500.398,-3485.252;Float;False;Property;_Outlines_Color_Opacity;Outlines_Color_Opacity;3;0;Create;True;0;0;False;0;2;1.5;0;10;0;1;FLOAT;0
Node;AmplifyShaderEditor.RangedFloatNode;282;4477.57,-1019.754;Float;False;Property;_FarDistanceMax;Far Distance Max;13;0;Create;True;0;0;False;0;1;0;0;5;0;1;FLOAT;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;246;5524.91,-3616.985;Float;False;3;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleDivideOpNode;111;5881.907,-15.46565;Float;False;2;0;FLOAT3;0,0,0;False;1;FLOAT3;100,100,100;False;1;FLOAT3;0
Node;AmplifyShaderEditor.PosVertexDataNode;103;6430.061,-205.4246;Float;False;0;0;5;FLOAT3;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.Vector2Node;172;2840.064,-3633.129;Float;False;Constant;_Vector0;Vector 0;5;0;Create;True;0;0;False;0;0.5,0.5;0,0;0;3;FLOAT2;0;FLOAT;1;FLOAT;2
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;169;2732.813,-3760.91;Float;False;2;2;0;FLOAT4;0,0,0,0;False;1;FLOAT4;0.5,0.5,0.5,0;False;1;FLOAT4;0
Node;AmplifyShaderEditor.ColorNode;220;5551.46,-3328.97;Float;False;Property;_Outlines_Color;Outlines_Color;1;0;Create;True;0;0;False;0;1,1,1,0;0.8612211,0.4157969,0.5985348,1;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SamplerNode;276;4793.512,-3522.693;Float;True;Property;_Outlines_Mask;Outlines_Mask;11;0;Create;True;0;0;False;0;None;None;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.RangedFloatNode;148;4323.112,-1083.088;Float;False;Constant;_Float2;Float 2;4;0;Create;True;0;0;False;0;0.002;0.002;0;0;0;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleAddOpNode;170;3021.909,-3756.439;Float;False;2;2;0;FLOAT4;0,0,0,0;False;1;FLOAT2;0,0;False;1;FLOAT4;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;283;4846.446,-1093.045;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.RangedFloatNode;230;5424.449,-1974.387;Float;False;Property;_Faces_Color_Opacity;Faces_Color_Opacity;5;0;Create;True;0;0;False;0;5;2.5;0;100;0;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;135;6019.492,-3509.44;Float;False;4;4;0;FLOAT;1;False;1;FLOAT;1;False;2;COLOR;0,0,0,0;False;3;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.RangedFloatNode;275;5911.504,-2522.938;Float;False;Property;_GearsOutlinesIntensity;Gears Outlines Intensity;10;0;Create;True;0;0;False;0;0;0;0;0;0;1;FLOAT;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;151;4307.521,-1200.334;Float;False;3;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.RotateAboutAxisNode;102;6648.437,-541.8487;Float;False;False;4;0;FLOAT3;0,0,1;False;1;FLOAT;0;False;2;FLOAT3;0,0,0;False;3;FLOAT3;0,0,0;False;1;FLOAT3;0
Node;AmplifyShaderEditor.ClampOpNode;224;5529.332,-2146.437;Float;False;3;0;FLOAT;0;False;1;FLOAT;0;False;2;FLOAT;10;False;1;FLOAT;0
Node;AmplifyShaderEditor.WireNode;241;6812.901,-1398.098;Float;False;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;274;6239.765,-2540.667;Float;False;2;2;0;COLOR;0,0,0,0;False;1;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.ColorNode;263;5483.047,-1879.302;Float;False;Property;_Faces_Color;Faces_Color;4;0;Create;True;0;0;False;0;1,1,1,0;0,0,0,0;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.TextureCoordinatesNode;250;7486.628,-29.92402;Float;False;2;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleSubtractOpNode;106;7320.88,-228.4021;Float;False;2;0;FLOAT3;0,0,0;False;1;FLOAT3;0,0,0;False;1;FLOAT3;0
Node;AmplifyShaderEditor.WireNode;240;6719.709,-1669.298;Float;False;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SamplerNode;173;3192.626,-3901.889;Float;True;Property;_DiffuseMap;DiffuseMap;6;0;Create;True;0;0;False;0;86fd02bbbfa0d014cbe155852e2fe672;86fd02bbbfa0d014cbe155852e2fe672;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.ColorNode;134;3837.663,-3728.501;Float;False;Property;_SurfaceColor;Surface Color;0;0;Create;True;0;0;False;0;1,1,1,0;1,1,1,0;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;147;4823.07,-1300.826;Float;False;3;3;0;COLOR;0,0,0,0;False;1;FLOAT;0;False;2;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;229;5867.966,-2110.581;Float;False;2;2;0;FLOAT;0;False;1;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.ClampOpNode;162;5047.545,-1114.548;Float;False;3;0;COLOR;0,0,0,0;False;1;COLOR;0,0,0,0;False;2;COLOR;1,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleAddOpNode;281;5603.219,-3730.681;Float;False;2;2;0;COLOR;0,0,0,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;218;7016.908,-2113.236;Float;False;4;4;0;FLOAT;0;False;1;COLOR;0,0,0,0;False;2;FLOAT;0;False;3;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;284;6692.057,-2516.082;Float;False;3;3;0;COLOR;0,0,0,0;False;1;FLOAT;0;False;2;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;121;7803.842,-235.0967;Float;False;2;2;0;FLOAT3;0,0,0;False;1;FLOAT;1;False;1;FLOAT3;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;176;5599.769,-3837.462;Float;False;2;2;0;COLOR;1,1,1,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleAddOpNode;273;7828.117,-2540.568;Float;False;2;2;0;COLOR;0,0,0,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleAddOpNode;142;7992.445,-797.2269;Float;False;2;2;0;FLOAT3;0,0,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.TextureCoordinatesNode;280;2802.889,-3484.586;Float;False;0;-1;2;3;2;SAMPLER2D;;False;0;FLOAT2;1,1;False;1;FLOAT2;0,0;False;5;FLOAT2;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleAddOpNode;131;6669.799,-3618.447;Float;False;2;2;0;COLOR;0,0,0,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.StandardSurfaceOutputNode;178;8578.216,-3520.755;Float;False;True;2;Float;ASEMaterialInspector;0;0;Standard;Letters_FX;False;False;False;False;False;False;False;False;False;False;False;False;False;False;True;False;False;False;False;False;Off;0;False;-1;0;False;-1;False;0;False;-1;0;False;-1;False;0;Custom;0.5;True;True;0;True;Transparent;;Geometry;ForwardOnly;True;True;True;True;True;True;True;True;True;True;True;True;True;True;True;True;True;0;False;-1;False;0;False;-1;255;False;-1;255;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;False;2;15;10;25;False;0.5;True;2;5;False;-1;10;False;-1;0;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;0;0.1650943,1,0.3878069,0;VertexOffset;True;False;Cylindrical;False;Relative;0;;2;-1;-1;-1;0;False;0;0;False;-1;-1;0;False;-1;0;0;0;16;0;FLOAT3;0,0,0;False;1;FLOAT3;0,0,0;False;2;FLOAT3;0,0,0;False;3;FLOAT;0;False;4;FLOAT;0;False;5;FLOAT;0;False;6;FLOAT3;0,0,0;False;7;FLOAT3;0,0,0;False;8;FLOAT;0;False;9;FLOAT;0;False;10;FLOAT;0;False;13;FLOAT3;0,0,0;False;11;FLOAT3;0,0,0;False;12;FLOAT3;0,0,0;False;14;FLOAT4;0,0,0,0;False;15;FLOAT3;0,0,0;False;0
WireConnection;161;0;160;3
WireConnection;159;1;161;0
WireConnection;205;0;201;2
WireConnection;204;0;201;1
WireConnection;243;1;159;0
WireConnection;272;0;225;0
WireConnection;206;0;204;0
WireConnection;144;0;149;0
WireConnection;144;1;243;1
WireConnection;207;0;205;0
WireConnection;209;0;207;0
WireConnection;228;0;144;0
WireConnection;208;0;206;0
WireConnection;270;0;272;0
WireConnection;127;0;126;1
WireConnection;237;0;228;0
WireConnection;212;0;208;0
WireConnection;212;1;270;0
WireConnection;213;0;209;0
WireConnection;213;1;270;0
WireConnection;215;0;213;0
WireConnection;215;1;216;0
WireConnection;214;0;212;0
WireConnection;214;1;216;0
WireConnection;256;0;237;0
WireConnection;99;0;95;1
WireConnection;232;0;127;0
WireConnection;232;1;233;0
WireConnection;217;0;214;0
WireConnection;217;1;215;0
WireConnection;217;2;243;1
WireConnection;118;0;120;1
WireConnection;171;0;165;1
WireConnection;171;1;165;2
WireConnection;97;0;99;0
WireConnection;97;1;95;2
WireConnection;97;2;96;1
WireConnection;278;0;277;0
WireConnection;278;2;279;0
WireConnection;234;0;232;0
WireConnection;234;1;256;0
WireConnection;221;0;217;0
WireConnection;221;1;222;0
WireConnection;117;0;118;0
WireConnection;117;1;120;2
WireConnection;117;2;120;3
WireConnection;244;0;234;0
WireConnection;244;1;245;4
WireConnection;111;0;97;0
WireConnection;169;0;171;0
WireConnection;276;1;278;0
WireConnection;170;0;169;0
WireConnection;170;1;172;0
WireConnection;283;0;148;0
WireConnection;283;1;282;0
WireConnection;135;0;246;2
WireConnection;135;1;138;0
WireConnection;135;2;220;0
WireConnection;135;3;276;1
WireConnection;102;0;117;0
WireConnection;102;1;244;0
WireConnection;102;2;111;0
WireConnection;102;3;103;0
WireConnection;224;0;221;0
WireConnection;241;0;151;1
WireConnection;274;0;135;0
WireConnection;274;1;275;0
WireConnection;106;0;102;0
WireConnection;106;1;103;0
WireConnection;240;0;228;0
WireConnection;173;1;170;0
WireConnection;147;0;144;0
WireConnection;147;1;151;1
WireConnection;147;2;283;0
WireConnection;229;0;224;0
WireConnection;229;1;230;0
WireConnection;162;0;147;0
WireConnection;162;2;283;0
WireConnection;281;0;173;0
WireConnection;281;1;134;0
WireConnection;218;0;229;0
WireConnection;218;1;263;0
WireConnection;218;2;240;0
WireConnection;218;3;241;0
WireConnection;284;0;274;0
WireConnection;284;1;228;0
WireConnection;284;2;151;1
WireConnection;121;0;106;0
WireConnection;121;1;250;2
WireConnection;176;0;173;0
WireConnection;176;1;134;0
WireConnection;273;0;284;0
WireConnection;273;1;218;0
WireConnection;142;0;121;0
WireConnection;142;1;162;0
WireConnection;131;0;281;0
WireConnection;131;1;135;0
WireConnection;178;0;131;0
WireConnection;178;2;273;0
WireConnection;178;11;142;0
ASEEND*/
//CHKSM=04174C5630D4590EE7F47D91BB6217BEC2384A87