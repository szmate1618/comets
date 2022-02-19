using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    void Update()
    {
		float orthographicSize = Camera.main.orthographicSize;
		orthographicSize += Input.GetAxis("zoom") * 10;
		orthographicSize = Mathf.Clamp(orthographicSize, 5, 100);
		Camera.main.orthographicSize = orthographicSize;
	}
}
