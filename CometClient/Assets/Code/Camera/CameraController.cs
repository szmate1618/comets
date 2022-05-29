using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
	void Update()
	{
		float orthographicSize = GetComponent<Camera>().orthographicSize;
		orthographicSize += Input.GetAxis("zoom") * 10;
		orthographicSize = Mathf.Clamp(orthographicSize, 5, 100);
		GetComponent<Camera>().orthographicSize = orthographicSize;
	}
}
