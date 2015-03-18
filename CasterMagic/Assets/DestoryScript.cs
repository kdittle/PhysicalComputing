using UnityEngine;
using System.Collections;

public class DestoryScript : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
	{
	
	}
	
	// Update is called once per frame
	void Update () 
	{
	
	}

	void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag == "Enemy") 
		{
			PlayerScript.Health = PlayerScript.Health - EnemyScript.damage;
			Destroy(other.gameObject);
		}
	}
}
