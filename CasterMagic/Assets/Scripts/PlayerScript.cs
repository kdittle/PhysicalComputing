using UnityEngine;
using System.Collections;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Collections.Generic;

public class PlayerScript : MonoBehaviour
{
    private int Health;
    private int _curHealth;
    public static int Score;
    public static bool isDead;
    public bool isPlaying = false;

    public float distance;

    public GameObject PlayerArm;
    public Quaternion PlArmIdentity;
    public GUIStyle style;
    public GameObject[] Spells;
    private GameObject CastingSpell;
    private GameObject TempSpell;

    public List<GameObject> enemies;
    public GameObject selectedEnemy;

    public Texture2D reticle;
    public Rect retRect;

    public bool isCharging = false;
    public float nativeRatio;
    public bool isPaused = false;

    public float checkTimer = 0;
    private SerialPort _serialPort;
    private bool _isPortOpen = false;

    // Use this for initialization
    void Start()
    {
        //Screen.showCursor = false;
        isPlaying = false;

        //Health = 100;
        isDead = false;

        Health = 100;
        _curHealth = Health;

        PlArmIdentity = PlayerArm.transform.rotation;

        Instantiate(Spells[0], PlayerArm.transform.GetChild(0).position, Quaternion.identity);
        CastingSpell = GameObject.FindGameObjectWithTag("Spell");

        string[] ports = SerialPort.GetPortNames();

        //		foreach (string port in ports)
        //		{
        //			Console.WriteLine(port);
        //		}

        _serialPort = new SerialPort(ports[1], 9600);
        _serialPort.Open();
        Debug.Log(_serialPort.PortName);
        Debug.Log(_serialPort.BaudRate);
        Debug.Log(_serialPort.IsOpen);
    }

    // Update is called once per frame
    void Update()
    {

        if (Health <= 0)
            isDead = true;

        if (_curHealth != Health)
        {
            //Debug.Log("SHIT");
            _curHealth = Health;
            _serialPort.WriteLine("r");
        }

        if (!isDead && isPlaying)
        {
            //find all enemies and add them to this list
            foreach (GameObject t in GameObject.FindGameObjectsWithTag("Enemy"))
            {
                //check to see if the enemy is on the list already or not
                if (!enemies.Contains(t))
                    enemies.Add(t); //add the new enemy but not the old ones
            }

            //iterate through the list and find out if enemies are missing
            //missing enemies come from them being destoryed.
            //remove these enemies so that targetting can actually take place.
            for (int i = 0; i < enemies.Count; i++)
            {
                if (enemies[i] == null)
                    enemies.Remove(enemies[i]);
            }

            //Target the enemy
            //Allows for space to be pressed multple times to scroll through possible targets
            if (Input.GetKeyDown(KeyCode.A))
            {
                TargetEnemy();
                //PlayerArm.transform.LookAt(selectedEnemy.transform.position);
            }
            //else
            //    PlayerArm.transform.localRotation = PlArmIdentity;

            if(selectedEnemy != null)
            {
                PlayerArm.transform.LookAt(selectedEnemy.transform.position);
            }
            else
                PlayerArm.transform.localRotation = PlArmIdentity;

            //if the mouse button is pressed, the the 
            if (Input.GetKeyDown(KeyCode.Mouse0) && selectedEnemy != null)
            {
                //main spell stuff
                CastingSpell.particleSystem.transform.position = PlayerArm.transform.GetChild(0).position;
                CastingSpell.gameObject.particleSystem.Play();

                //create the temp spell that will be shot
                TempSpell = Instantiate(CastingSpell, PlayerArm.transform.GetChild(0).position, Quaternion.identity) as GameObject;
            }

            if (Input.GetKeyUp(KeyCode.Mouse0) && selectedEnemy != null)
            {
                //other casting stuff
                CastingSpell.particleSystem.transform.position = PlayerArm.transform.GetChild(0).position;
                CastingSpell.gameObject.particleSystem.Stop();

                //switch to playing the temp particle
                TempSpell.particleSystem.Play();
                TempSpell.transform.position = PlayerArm.transform.GetChild(0).position;
                
                //shoot the spell
                TempSpell.rigidbody.AddRelativeForce(Vector3.forward * 1000);
                TempSpell.AddComponent<SphereCollider>();
                TempSpell.collider.enabled = true;
                TempSpell.GetComponent<SpellScript>().FollowTarget(selectedEnemy);
            }

        }
    }

    void OnGUI()
    {
        if(isPlaying)
            GUI.Label(new Rect(Screen.width / 2, 0, 200, 100), "" + Score, style);
    }

    public void StartGame()
    {
        isPlaying = true;
    }

    public void UpdateHealth(int x)
    {
        Health -= x;
        Debug.Log("Updated Health");
        Debug.Log(Health);
    }

    public void TargetEnemy()
    {
        //if the selected enemy is null, make the first enemy in the list selected
        if (selectedEnemy == null)
        {
            selectedEnemy = enemies[0];
        }
        else
        {
            //find the index of the current enemy
            int index = enemies.IndexOf(selectedEnemy);

            //increment index every time the target button is pressed
            if (index < enemies.Count - 1)
                index++;
            else
                index = 0;      //reset the index to 0

            selectedEnemy = enemies[index]; //update the selected enemy
        }
    }
}
