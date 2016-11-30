using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.IO;
public class movie : MonoBehaviour
{

    public MovieTexture mov;
    public AudioSource aud;
    public static float timespan;
    public float checktime;
    public string logPath = "C:/Users/mobile_lab_01/Documents/Visual Studio 2013/Projects/opencv_0520/opencvex/Release/log.txt";
    public float speed;
    public float averageSpeed = 20.0f;
    public float pit = 0.0f;
    public static int count_checktime;
    public static float[] speedarr = new float[1000];
    // Use this for initialization

    void Start()
    {
        GetComponent<Renderer>().material.mainTexture = mov;
        aud = GetComponent<AudioSource>();

        timespan = 0.0f;
        checktime = 3.0f;
                        
        aud.clip = mov.audioClip;
        aud.pitch = 1.0f;

        mov.Play();
        aud.Play();

    }
    // Update is called once per frame
    void Update()
    {
       try
        {
            FileStream file = new FileStream(logPath, FileMode.Open, FileAccess.Read, FileShare.Read);
            StreamReader sr = new StreamReader(file);
            string str = null;
            str = sr.ReadLine();
            speed = float.Parse(str);
            sr.Dispose();
            Debug.Log(speed);
        }
        catch(IOException e)
        {
             Debug.Log(speed);
        }
        
  
        timespan += Time.deltaTime;
        
        if (timespan > checktime)
        {
            mov.Pause();
            aud.Pause();

            checktime += 3.0f;
            count_checktime++;
            speedarr[count_checktime] = speed;

            
            if(speed <10)
            {
                aud.pitch *= 1;
            }
             else
            {
                aud.pitch = speed / averageSpeed;     
                 if(aud.pitch >= 2.0f)
                {
                    aud.pitch = 2.0f;
                }
                 else if(aud.pitch <= 0.5f)
                {
                     aud.pitch = 0.5f;
                }
                
             }

            pit = aud.pitch;

            if (!mov.isPlaying)
            {  
                mov.Play();
                aud.Play();
            }
        }
        if(Input.GetKey(KeyCode.P) == true)
        {
            Application.LoadLevel("LastScene");
        }
    
        if((mov.isPlaying) && timespan>530)
        {
            Application.LoadLevel("LastScene");
        }

    }
}
