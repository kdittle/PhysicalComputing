using UnityEngine;
using System.Collections;

public class EnemyScript : MonoBehaviour 
{
	public float EnemySpeed;

	public static int health;
	public static int damage;

	// Use this for initialization
	void Start () 
	{
		health = 10;
		damage = 10;
	}
	
	// Update is called once per frame
	void FixedUpdate () 
	{
		rigidbody.AddForce (-Vector3.forward * EnemySpeed);
	}
}
