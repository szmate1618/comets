using UnityEngine;

public class FisheyeCameraController : MonoBehaviour
{

	public Shader fisheyeShader;

	private void Start ()
	{
		GetComponent<Camera>().SetReplacementShader(fisheyeShader, "");
	}

	void OnPreCull()
	{
		GetComponent<Camera>().cullingMatrix =
			Matrix4x4.Ortho(-99999, 99999, -99999, 99999, 0.001f, 99999) *
			Matrix4x4.Translate(Vector3.forward * -99999 / 2f) *
			Camera.main.worldToCameraMatrix;
	}

}
