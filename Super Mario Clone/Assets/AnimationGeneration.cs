using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class AnimationGeneration : MonoBehaviour
{
    //public string[] sub_Dirs = System.IO.Directory.GetDirectories("D:/University/Super Mario Clone/Assets/Resources/Sprite_Animations");
    //public string[] sub_Dirs_Names;
    //public UnityEditor.Animations.AnimatorController controller;

    //public List<AnimationClip> clips = new List<AnimationClip>();
    //public List<Sprite> sprites_ = new List<Sprite>();


    ////Some of this code here is nice for reimporting and standartization and some other shit is nice for making stuff in code

    //[MenuItem("Assets/Pixels Per Unit to 1 and FilterMode to Pixel")]
    //void Awake()
    //{








    //    sub_Dirs_Names = new string[sub_Dirs.Length];
    //    for (int i = 0; i < sub_Dirs.Length; i++)
    //    {
    //        sub_Dirs_Names[i] = new System.IO.DirectoryInfo(sub_Dirs[i]).Name;

    //        //string[] files = null;
    //        //files = System.IO.Directory.GetFiles(sub_Dirs[i]);
    //    }


    //    //Sprite[] sprites = Resources.LoadAll<Sprite>("Sprite_Animations/" + sub_Dirs_Names[i]);

    //    //for (int index = 0; index < sprites.Length; index++)
    //    //{

    //    //string path = AssetDatabase.GetAssetPath(sprites[index]);






    //    //        //print(files[index]);

    //    //        //TextureImporter importer = (TextureImporter)AssetImporter.GetAtPath(path);
    //    //        //importer.spritePixelsPerUnit = 1;
    //    //        //importer.filterMode = FilterMode.Point;
    //    //        //importer.SaveAndReimport();

    //    //    }

    //    //}


    //    //}

    //    //foreach (string directory in sub_Dirs_Names)
    //    //{
    //    //    Sprite[] files = null;

    //    //    files = Resources.LoadAll<Sprite>("Sprite_Animations/" + directory);

    //    //    if (files != null)
    //    //    {
    //    //        for (int index = 0; index < files.Length; index++)
    //    //        {
    //    //            Sprite temp = files[index];
    //    //            temp = Sprite.Create(files[index].texture, files[index].rect, files[index].pivot, 1.0f);
    //    //            files[index] = temp;

    //    //        }

    //    //    }
    //    //}






    //    //for (int index = 0; index < sub_Dirs.Length; index++)
    //    //{
    //    //    //Uncomment this and comment the other part to generate the animation files from a template file
    //    //    //Then comment this part, uncomment the other part to create the animations based on the sprites in a folder
    //    //    //System.IO.File.Copy("D:/University/Super Mario Clone/Assets/Resources/Empty.anim",
    //    //    //                    "D:/University/Super Mario Clone/Assets/Resources/Clips/" + sub_Dirs_Names[index] + ".anim");

    //    //    var clip = Resources.Load<AnimationClip>("Clips/" + sub_Dirs_Names[index]);
    //    //    Sprite[] sprites = Resources.LoadAll<Sprite>("Sprite_Animations/" + sub_Dirs_Names[index]);
    //    //    //Clip operation
    //    //    EditorCurveBinding spriteBinding = new EditorCurveBinding();
    //    //    spriteBinding.type = typeof(SpriteRenderer);
    //    //    spriteBinding.path = "";
    //    //    spriteBinding.propertyName = "m_Sprite";

    //    //    ObjectReferenceKeyframe[] spriteKeyFrames = new ObjectReferenceKeyframe[sprites.Length];
    //    //    for (int i = 0; i < (sprites.Length); i++)
    //    //    {
    //    //        print(sprites[i]);
    //    //        spriteKeyFrames[i] = new ObjectReferenceKeyframe();
    //    //        spriteKeyFrames[i].time = i / 10.0f;
    //    //        spriteKeyFrames[i].value = sprites[i];
    //    //    }

    //    //    AnimationUtility.SetObjectReferenceCurve(clip, spriteBinding, spriteKeyFrames);

    //    //    controller.AddMotion(clip);

    //    //    print(sprites.Length);
    //    //}







    //    //foreach (string name in sub_Dirs_Names)
    //    //{
    //    //    string[] lines = System.IO.File.ReadAllLines("D:/University/Super Mario Clone/Assets/Resources/Clips/" + name + ".anim");

    //    //    for (int j = 0; j < lines.Length; j++)
    //    //    {
    //    //        if (lines[j] == ("  m_Legacy: 0"))

    //    //            lines[j] = "  m_Legacy: 1";

    //    //    }
    //    //    print("Im doing my job");

    //    //    System.IO.File.WriteAllLines("D:/University/Super Mario Clone/Assets/Resources/Clips/" + name + ".anim", lines);
    //    //    break;
    //    //}
    //}
}
    //private void Update()
    //{

    //    var test = EditorWindow.mouseOverWindow;
    //    EditorWindow editorWindow;
    //    editorWindow = EditorWindow.GetWindow(test.GetType());

    //    MonoBehaviour.print(EditorWindow.mouseOverWindow);
    //}





