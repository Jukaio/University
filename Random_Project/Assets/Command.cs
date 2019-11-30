using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Command : ScriptableObject
{
    static public int check_Axis_(KeyCode minus, KeyCode plus)
    {
        if (Input.GetKey(minus) && Input.GetKey(plus))
            return 0;
        if (Input.GetKey(minus) && !Input.GetKey(plus))
            return -1;
        if (Input.GetKey(plus) && !Input.GetKey(minus))
            return 1;
        return 0;
    }

    static public Vector3 check_Both_DPad_Axes_(KeyCode x_minus, KeyCode x_plus, KeyCode y_minus, KeyCode y_plus)
    {
        int m_x, m_y, p_x, p_y;
        m_x = m_y = p_x = p_y = 0;
        if (Input.GetKey(x_plus))
            p_x = 1;
        if (Input.GetKey(y_plus))
            p_y = 1;
        if (Input.GetKey(x_minus))
            m_x = 1;
        if (Input.GetKey(y_minus))
            m_y = 1;

        return new Vector3((p_x - m_x), (p_y - m_y), 0).normalized;
    }

    static public Vector2 check_Four_Axes_(float x_minus, float x_plus, float y_minus, float y_plus)
    {
        return new Vector2((x_plus - x_minus), (y_plus - y_minus)).normalized;
    }

    static public int check_Axis_(KeyCode minus, KeyCode prev_Minus, KeyCode plus, KeyCode prev_Plus)
    {
        if (Input.GetKey(minus) && Input.GetKey(plus))
            return 0;
        if (Input.GetKey(prev_Minus) && !Input.GetKey(minus))
            return -1;
        if (Input.GetKey(prev_Plus) && !Input.GetKey(plus))
            return 1;
        return 0;
    }

    static public bool check_Pressed_(KeyCode button)
    {
        return Input.GetKeyDown(button);
    }

    static public bool check_Released_(KeyCode button)
    {
        return Input.GetKeyUp(button);
    }


}
