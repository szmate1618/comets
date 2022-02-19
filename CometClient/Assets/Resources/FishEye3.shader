Shader "FisheyeShader3"
{
	Properties
	{
		_MainTex("Texture", 2D) = "white" {}
	}
	SubShader
	{
		LOD 100
		Blend SrcAlpha OneMinusSrcAlpha
		Tags {"Queue" = "Transparent"}

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
				o.vertex = UnityObjectToClipPos(v.vertex);

				if (abs(o.vertex.x) > 0.75)
				{
					float sgn = sign(o.vertex.x);
					float excess = o.vertex.x - sgn * 0.75;
					excess /= max(sqrt((abs(excess) + 1) * 10), 0.000001);
					o.vertex.x = sgn * 0.75 + excess;
				}

				if (abs(o.vertex.y) > 0.75)
				{
					float sgn = sign(o.vertex.y);
					float excess = o.vertex.y - sgn * 0.75;
					excess /= max(sqrt((abs(excess) + 1) * 10), 0.000001);
					o.vertex.y = sgn * 0.75 + excess;
				}

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
