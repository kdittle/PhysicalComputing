using UnityEngine;
using System.Collections;

public class SpellScript : MonoBehaviour 
{

    private GameObject SpellObject;

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
        if (other.gameObject.tag == "DestroyTrigger")
        {
            Destroy(gameObject);
        }
    }

    void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.tag == "Enemy")
        {
            Destroy(gameObject);
            Destroy(other.gameObject);
            PlayerScript.Score += 25;
        }
    }
}
