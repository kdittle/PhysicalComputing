using UnityEngine;
using System.Collections;

public class EnemySpawner : MonoBehaviour 
{
	public GameObject Enemy;
	public float spawnInterval;
	public float curSpawnTime;

	public GameObject[] _SpawnList;


	// Use this for initialization
	void Start () 
	{
		_SpawnList = GameObject.FindGameObjectsWithTag ("EnemySpawn");
	}

	// Update is called once per frame
	void FixedUpdate () 
	{
		curSpawnTime++;

		if (curSpawnTime >= spawnInterval) 
		{
			GameObject spawn = _SpawnList[Random.Range(0, _SpawnList.Length)];
			Instantiate (Enemy, spawn.transform.position, Quaternion.identity);
			curSpawnTime = 0;
		}

	}
}
