using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundManager : MonoBehaviour
{
	public GameObject backgroundTile;
	public int  columnCount;
	public int  rowCount;
	public float tileWidth;
	public float tileHeight;

	void Start()
    {
		for (int i = 0; i < columnCount; i++)
		{
			for (int j = 0; j < rowCount; j++)
			{
				GameObject newTile = Instantiate(backgroundTile);
				newTile.transform.localScale = new Vector3(tileWidth, tileHeight, 1);
				newTile.transform.position = new Vector3(
					-(tileWidth * columnCount) / 2.0f + tileWidth / 2.0f + tileWidth * i, 
					-(tileHeight * rowCount) / 2.0f + tileHeight / 2.0f + tileHeight * j,
					9
				);
			}
		}
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
