using UnityEngine;
using System.Collections;

public class DestoryScript : MonoBehaviour
{
    private PlayerScript ps;

	// Use this for initialization
    private void Start()
    {
        ps = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerScript>();
    }


    // Update is called once per frame
	void Update () 
	{
	
	}

	void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag == "Enemy") 
		{
			ps.UpdateHealth(EnemyScript.damage);
			Destroy(other.gameObject);
		}
	}
}
