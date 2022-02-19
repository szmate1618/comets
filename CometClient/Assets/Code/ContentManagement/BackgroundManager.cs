using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundManager : MonoBehaviour
{
	public GameObject mainCamera;
	public GameObject backgroundTile;
	public int  columnCount;
	public int  rowCount;
	public float tileWidth;
	public float tileHeight;

	private GameObject[,] tiles;

	void Start()
 {
		tiles = new GameObject[rowCount, columnCount];
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				tiles[i, j] = Instantiate(backgroundTile);
				tiles[i, j].transform.localScale = new Vector3(tileWidth, tileHeight, 1);
				tiles[i, j].transform.position = new Vector3(
					-(tileWidth * columnCount) / 2.0f + tileWidth / 2.0f + tileWidth * i, 
					-(tileHeight * rowCount) / 2.0f + tileHeight / 2.0f + tileHeight * j,
					9
				);
			}
		}
 }

 void Update()
 {
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				float currentX = tiles[i, j].transform.position.x;
				float currentY = tiles[i, j].transform.position.y;
				float newX = currentX;
				float newY = currentY;
				if (currentX - mainCamera.transform.position.x > (tileWidth * columnCount) / 2.0f)
				{
					newX = currentX - tileWidth * columnCount;
				}
				if (currentX - mainCamera.transform.position.x < -(tileWidth * columnCount) / 2.0f)
				{
					newX = currentX + tileWidth * columnCount;
				}
				if (currentY - mainCamera.transform.position.y > (tileWidth * columnCount) / 2.0f)
				{
					newY = currentY - tileWidth * columnCount;
				}
				if (currentY - mainCamera.transform.position.y < -(tileWidth * columnCount) / 2.0f)
				{
					newY = currentY + tileWidth * columnCount;
				}

				if (newX != currentX || newY != currentY)
				{
					tiles[i, j].transform.position = new Vector3(newX, newY, tiles[i, j].transform.position.z);
				}
			}
		}
	}
}
