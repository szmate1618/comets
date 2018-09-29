using UnityEngine;

public class MainCameraController : MonoBehaviour
{

	public Shader fishEyeShader;

	private void Start ()
	{
		Camera.main.SetReplacementShader(fishEyeShader, "");
	}

	void OnPreCull()
	{
		Camera.main.cullingMatrix = Matrix4x4.Ortho(-99999, 99999, -99999, 99999, 0.001f, 99999) *
							Matrix4x4.Translate(Vector3.forward * -99999 / 2f) *
							Camera.main.worldToCameraMatrix;
	}

}
