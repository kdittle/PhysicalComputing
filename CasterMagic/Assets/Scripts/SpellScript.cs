using UnityEngine;
using System.Collections;

public class SpellScript : MonoBehaviour 
{
    private GameObject target;

	// Use this for initialization
	void Start () 
    {
	
	}
	
	// Update is called once per frame
	void Update () 
    {
        transform.localRotation = GameObject.FindGameObjectWithTag("PlayerArm").gameObject.transform.localRotation;

        //if(target != null)
        //{
        //    float yAngle = target.transform.localRotation.y - transform.localRotation.y;
        //    float xAngle = target.transform.localRotation.x - transform.localRotation.x;

        //    Vector3 newVec = new Vector3(xAngle, yAngle, 0.0f);
        //}
	}

    public void FollowTarget(GameObject _target)
    {
        target = _target;
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
