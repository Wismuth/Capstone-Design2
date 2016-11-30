using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class avg_speed : MonoBehaviour {

    public Text counterText;
    public float speed_sum;
    public float result_speed;
    // Use this for initialization
    void Start () {
        counterText = GetComponent<Text>() as Text;
        for(int i = 0; i<movie.count_checktime; i++)
        {
            speed_sum += movie.speedarr[movie.count_checktime];
        }

        result_speed = speed_sum / movie.count_checktime;
        counterText.text = "Avg Speed : " + result_speed.ToString("00");
    }
	
	// Update is called once per frame
	void Update () {


    
    }
}
