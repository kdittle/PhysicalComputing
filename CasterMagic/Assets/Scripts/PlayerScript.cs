﻿using UnityEngine;
using System.Collections;
using System.IO;
using System.IO.Ports;
using System.Text;

public class PlayerScript : MonoBehaviour 
{
	public static int Health;
	public static int Score;

    public float distance;

	public GUIStyle style;
    public GameObject Spell;
    private GameObject CastingSpell;

	public Texture2D reticle;
    public Rect retRect;

    public bool isCharging = false;
	public float nativeRatio;

    public float checkTimer = 0;
	private SerialPort _serialPort;
	private bool _isPortOpen = false;

	// Use this for initialization
	void Start () 
	{
		Screen.showCursor = false;

		Health = 100;

	    


	    //CastingSpell = GameObject.FindGameObjectWithTag("Spell");

	    //tempParticle = Instantiate(particle, new Vector3(transform.position.x, transform.position.y, transform.position.z + distance), Quaternion.identity) as GameObject;

//        string[] ports = SerialPort.GetPortNames();

////		foreach (string port in ports)
////		{
////			Console.WriteLine(port);
////		}

//        _serialPort = new SerialPort(ports[1], 9600);
//        _serialPort.Open();
//        Debug.Log(_serialPort.PortName);
//        Debug.Log(_serialPort.BaudRate);
//        Debug.Log(_serialPort.IsOpen);
	}
	
	// Update is called once per frame
	void FixedUpdate ()
	{

        //checkTimer++;

        //if (checkTimer >= 30) 
        //{
        //    _serialPort.WriteLine ("r");
			
        //    string value = _serialPort.ReadLine (); //read info
        //    string[] vec3 = value.Split (','); //get 3 part value from arduino
			
        //    //vec3[0] holds the brake/backwards value
        //    if (vec3 [0] != "") 
        //    {
        //        positionVec.x = float.Parse(vec3[0]);
        //    }

        //    if(vec3 [1] != "")
        //    {
        //        positionVec.y = float.Parse(vec3[1]);
        //    }

        //    Debug.Log("Serial Checked.");

        //    checkTimer = 0;
        //}

	    if (isCharging)
	    {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            Vector3 pos = ray.GetPoint(distance);
            CastingSpell.particleSystem.transform.position = pos;
	    }

        if (Input.GetMouseButtonDown(0))
        {

            CastingSpell.gameObject.particleSystem.Play();

            isCharging = true;
        }

        if (Input.GetMouseButtonUp(0))
        {
            Spell.rigidbody.AddForce(Vector3.forward * 1000);
            isCharging = false;
        }

        retRect = new Rect(Screen.width - (Screen.width - Input.mousePosition.x) - (reticle.width / 2), (Screen.height - Input.mousePosition.y) - (reticle.height / 2), reticle.width, reticle.height);

	}

    public void CastSpell()
    {
        
    }

	void OnGUI()
	{
		GUI.Label(new Rect(Screen.width / 2, 0, 200, 100), "Score: " + Score, style);

        GUI.DrawTexture(retRect, reticle);

	}
}
