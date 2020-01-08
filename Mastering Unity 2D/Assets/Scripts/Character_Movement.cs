using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Character_Movement : MonoBehaviour
{
    private Rigidbody2D player_Rigidbody2D;
    private bool facing_Right_;
    public float speed = 4.0f;

    private void Awake()
    {
        player_Rigidbody2D = (Rigidbody2D)GetComponent(typeof(Rigidbody2D));
    }


    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float move_Player_Vector = Input.GetAxis("Horizontal");
        player_Rigidbody2D.velocity = new Vector2(move_Player_Vector * speed, player_Rigidbody2D.velocity.y);

        if (move_Player_Vector > 0 && !facing_Right_)
            Flip();
        else if (move_Player_Vector < 0 && facing_Right_)
            Flip();
    }

    void Flip()
    {
        facing_Right_ = !facing_Right_;
        Vector3 temp_Scale = transform.localScale;
        temp_Scale.x *= -1;
        transform.localScale = temp_Scale;
    }
}
