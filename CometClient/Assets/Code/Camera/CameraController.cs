using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
		float orthographicSize = Camera.main.orthographicSize;
		orthographicSize += Input.GetAxis("zoom") * 10;
		orthographicSize = Mathf.Clamp(orthographicSize, 5, 100);
		Camera.main.orthographicSize = orthographicSize;
	}
}
