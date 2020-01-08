using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stuff : MonoBehaviour
{
    public Vector3[] vertices_;
    public int vertex_Amount_;
    public int[] triangles_;

    public int width_ = 1280; 
    public int height_ = 1280;
    public int rows_ = 8;
    public int columns_ = 8;


    private void Start()
    {
        Create_Vertices();
        Create_Game_Object_On_Vertices();
    }

    public List<Vector3> List_ = new List<Vector3>();
    public Vector3[,] List_Mat_;
    void Create_Vertices()
    {
        for(int x = 0; x < width_; x += width_ / columns_)
        {
            for (int y = 0; y < height_; y += height_ / rows_)
            {
                List_.Add(new Vector3(x / 100.0f, y / 100.0f, 0));
            }
        }

        List_Mat_ = new Vector3[List_.Count / 8, List_.Count / 8];
        int index = 0;
        for(int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                List_Mat_[x, y] = List_[index];
                index++;
            }
        }
        print(List_Mat_.Length);
    }

    public GameObject test_; //Instantiate if you create something from prefabs
    void Create_Game_Object_On_Vertices()
    {
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                //GameObject test = new GameObject();
                //test.transform.position = List_Mat_[x, y];
                //test.transform.parent = gameObject.transform
                //If you create an object on the heap, just use new and it is automatically created. Don't use instantiate too.

                Instantiate<GameObject>(test_, List_Mat_[x, y], Quaternion.identity, gameObject.transform);
            }
        }

    }

    private void Update()
    {
        
    }
}
