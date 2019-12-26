using UnityEngine;


public class EntityFactory
{
	private TextureManager textureManager;

	public EntityFactory()
	{
		textureManager = new TextureManager();
	}

	public GameObject Create(net.ShapeDescription shapeDescription)
	{
		GameObject entity = new GameObject("Entity#" + shapeDescription.entity_id);
		entity.AddComponent<MeshFilter>();
		entity.AddComponent<MeshRenderer>();
		entity.GetComponent<MeshFilter>().mesh = MeshFactory.Create(shapeDescription.vertex_count, shapeDescription.triangle_count,
			shapeDescription.vertices, shapeDescription.uvs, shapeDescription.triangles);
		//TODO: Some kind of default material should be used here, so the fisheye could be turned off if desired.
		entity.GetComponent<MeshRenderer>().material = new Material(Resources.Load<Shader>("Fisheye"));
		entity.GetComponent<MeshRenderer>().material.mainTexture = textureManager.GetTexture(shapeDescription.texture_id);
		return entity;
	}

}
