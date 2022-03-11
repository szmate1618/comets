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
			Matrix4x4.Ortho(-99999, 99999, -99999, 99999, GetComponent<Camera>().nearClipPlane, GetComponent<Camera>().farClipPlane) *
			GetComponent<Camera>().worldToCameraMatrix;
	}

}
