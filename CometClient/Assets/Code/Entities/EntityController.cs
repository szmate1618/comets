using UnityEngine;


namespace entity
{

	public class EntityController : MonoBehaviour
	{

		private float stateLastUpdated;

		private void Start()
		{
			stateLastUpdated = Time.time;
		}

		private void Update()
		{
			if (Time.time - stateLastUpdated > def.Gameplay.entityObjectHideSeconds)
			{
				gameObject.SetActive(false);
			}
			if (Time.time - stateLastUpdated > def.Gameplay.entityObjectRemoveSeconds)
			{
				Destroy(gameObject);
			}
		}

		//This one is not an internal Unity function, but called explicitly.
		public void UpdateState(float x, float y, float phi)
		{
			stateLastUpdated = Time.time;
			if (!gameObject.activeInHierarchy) gameObject.SetActive(true);

			gameObject.transform.rotation = Quaternion.Euler(0, 0, Mathf.Rad2Deg * phi);
			gameObject.transform.position = new Vector3(x, y, 0);
		}
	}

}
