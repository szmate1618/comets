// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

// Upgrade NOTE: replaced '_World2Object' with 'unity_WorldToObject'

Shader "Unlit/FishEyeShader"
{
	Properties
	{
		_MainTex("Texture", 2D) = "white" {}
	}
	SubShader
	{
		Tags { "RenderType" = "Opaque" }
		LOD 100

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag

			#include "UnityCG.cginc"

			struct appdata
			{
				float4 vertex : POSITION;
				float2 uv : TEXCOORD0;
			};

			struct v2f
			{
				float2 uv : TEXCOORD0;
				float4 vertex : SV_POSITION;
			};

			sampler2D _MainTex;
			float4 _MainTex_ST;

			v2f vert(appdata v)
			{
				v2f o;
				/*float2 ObjSpaceCameraPos = mul(unity_WorldToObject, float4(_WorldSpaceCameraPos, 1.0)).xy;
				float2 offset = v.vertex.xy - ObjSpaceCameraPos;
				float l = length(offset);
				v.vertex.xy = ObjSpaceCameraPos + offset / sqrt(l);*/
				
				o.vertex = UnityObjectToClipPos(v.vertex);
				float l = length(o.vertex.xy);
				o.vertex.xy /= sqrt(l*5);
				o.uv = TRANSFORM_TEX(v.uv, _MainTex);
				return o;
			}

			fixed4 frag(v2f i) : SV_Target
			{
				fixed4 col = tex2D(_MainTex,  i.uv);
				return col;
			}
			ENDCG
		}
	}
}