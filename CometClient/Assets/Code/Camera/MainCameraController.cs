using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainCameraController : MonoBehaviour
{

	public Shader fishEyeShader;

	private void Start ()
	{
		/*Plane[] planes = GeometryUtility.CalculateFrustumPlanes(Camera.main);
		var asd = GetComponent<Camera>().cullingMatrix;
		GetComponent<Camera>().cullingMatrix = Matrix4x4.Frustum(-10.0f, 10.0f, -10.0f, 11.0f, 0.3f, 110.0f);
		//fishEyeShader = Shader.Find("FishEye");
		Plane[] planes2 = GeometryUtility.CalculateFrustumPlanes(Camera.main);
		var qwe = GetComponent<Camera>().cullingMatrix;*/
		GetComponent<Camera>().SetReplacementShader(fishEyeShader, "");
	}

	void OnPreCull()
	{
		Camera.main.cullingMatrix = Matrix4x4.Ortho(-99999, 99999, -99999, 99999, 0.001f, 99999) *
							Matrix4x4.Translate(Vector3.forward * -99999 / 2f) *
							Camera.main.worldToCameraMatrix;
	}

		/*private void OnRenderImage(RenderTexture src, RenderTexture dst)
		{
			//fishEyeShader = Shader.Find("FishEye");
			var cam = GetComponent<Camera>();//.SetReplacementShader(fishEyeShader, "");
			Graphics.Blit(src, dst, new Material(fishEyeShader));
		}*/

	}
