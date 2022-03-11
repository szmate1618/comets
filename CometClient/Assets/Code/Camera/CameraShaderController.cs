using UnityEngine;


public class CameraShaderController : MonoBehaviour
{
	public Shader shader;

	private void Start ()
	{
		GetComponent<Camera>().SetReplacementShader(shader, "");
	}

	void OnPreCull()
	{
		GetComponent<Camera>().cullingMatrix =
			Matrix4x4.Ortho(-99999, 99999, -99999, 99999, GetComponent<Camera>().nearClipPlane, GetComponent<Camera>().farClipPlane) *
			GetComponent<Camera>().worldToCameraMatrix;
	}

}
