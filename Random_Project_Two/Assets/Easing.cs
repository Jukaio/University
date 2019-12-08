using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Easing
{
    public static class EasingFunction
    {
        public enum Ease
        {
            EaseInQuad = 0,
            EaseOutQuad,
            EaseInOutQuad,
            EaseInCubic,
            EaseOutCubic,
            EaseInOutCubic,
            EaseInQuart,
            EaseOutQuart,
            EaseInOutQuart,
            EaseInQuint,
            EaseOutQuint,
            EaseInOutQuint,
            EaseInSine,
            EaseOutSine,
            EaseInOutSine,
            EaseInExpo,
            EaseOutExpo,
            EaseInOutExpo,
            EaseInCirc,
            EaseOutCirc,
            EaseInOutCirc,
            EaseInBounce,
            EaseOutBounce,
            EaseInOutBounce,
            EaseInBack,
            EaseOutBack,
            EaseInOutBack,
            EaseInElastic,
            EaseOutElastic,
            EaseInOutElastic,
        }

        private const float NATURAL_LOG_OF_2 = 0.693147181f;

        //
        // Easing functions
        //

        public static double EaseInSine(double t)
        {
            return Math.Sin(1.5707963 * t);
        }

        public static double EaseOutSine(double t)
        {
            return 1 + Math.Sin(1.5707963 * (--t));
        }

        public static double EaseInOutSine(double t)
        {
            return 0.5 * (1 + Math.Sin(3.1415926 * (t - 0.5)));
        }

        public static double EaseInQuad(double t)
        {
            return t * t;
        }

        public static double EaseOutQuad(double t)
        {
            return t * (2 - t);
        }

        public static double EaseInOutQuad(double t)
        {
            return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
        }

        public static double EaseInCubic(double t)
        {
            return t * t * t;
        }

        public static double EaseOutCubic(double t)
        {
            return 1 + (--t) * t * t;
        }

        public static double EaseInOutCubic(double t)
        {
            return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
        }

        public static double EaseInQuart(double t)
        {
            t *= t;
            return t * t;
        }

        public static double EaseOutQuart(double t)
        {
            t = (--t) * t;
            return 1 - t * t;
        }

        public static double EaseInOutQuart(double t)
        {
            if (t < 0.5)
            {
                t *= t;
                return 8 * t * t;
            }
            else
            {
                t = (--t) * t;
                return 1 - 8 * t * t;
            }
        }

        public static double EaseInQuint(double t)
        {
            double t2 = t * t;
            return t * t2 * t2;
        }

        public static double EaseOutQuint(double t)
        {
            double t2 = (--t) * t;
            return 1 + t * t2 * t2;
        }

        public static double EaseInOutQuint(double t)
        {
            double t2;
            if (t < 0.5)
            {
                t2 = t * t;
                return 16 * t * t2 * t2;
            }
            else
            {
                t2 = (--t) * t;
                return 1 + 16 * t * t2 * t2;
            }
        }

        public static double EaseInExpo(double t)
        {
            return (Math.Pow(2, 8 * t) - 1) / 255;
        }

        public static double EaseOutExpo(double t)
        {
            return 1 - Math.Pow(2, -8 * t);
        }

        public static double EaseInOutExpo(double t)
        {
            if (t < 0.5)
            {
                return (Math.Pow(2, 16 * t) - 1) / 510;
            }
            else
            {
                return 1 - 0.5 * Math.Pow(2, -16 * (t - 0.5));
            }
        }

        public static double EaseInCirc(double t)
        {
            return 1 - Math.Sqrt(1 - t);
        }

        public static double EaseOutCirc(double t)
        {
            return Math.Sqrt(t);
        }

        public static double EaseInOutCirc(double t)
        {
            if (t < 0.5)
            {
                return (1 - Math.Sqrt(1 - 2 * t)) * 0.5;
            }
            else
            {
                return (1 + Math.Sqrt(2 * t - 1)) * 0.5;
            }
        }

        public static double EaseInBack(double t)
        {
            return t * t * (2.70158 * t - 1.70158);
        }

        public static double EaseOutBack(double t)
        {
            return 1 + (--t) * t * (2.70158 * t + 1.70158);
        }

        public static double EaseInOutBack(double t)
        {
            if (t < 0.5)
            {
                return t * t * (7 * t - 2.5) * 2;
            }
            else
            {
                return 1 + (--t) * t * 2 * (7 * t + 2.5);
            }
        }

        public static double EaseInElastic(double t)
        {
            double t2 = t * t;
            return t2 * t2 * Math.Sin(t * Math.PI * 4.5);
        }

        public static double EaseOutElastic(double t)
        {
            double t2 = (t - 1) * (t - 1);
            return 1 - t2 * t2 * Math.Cos(t * Math.PI * 4.5);
        }

        public static double EaseInOutElastic(double t)
        {
            double t2;
            if (t < 0.45)
            {
                t2 = t * t;
                return 8 * t2 * t2 * Math.Sin(t * Math.PI * 9);
            }
            else if (t < 0.55)
            {
                return 0.5 + 0.75 * Math.Sin(t * Math.PI * 4);
            }
            else
            {
                t2 = (t - 1) * (t - 1);
                return 1 - 8 * t2 * t2 * Math.Sin(t * Math.PI * 9);
            }
        }

        public static double EaseInBounce(double t)
        {
            return Math.Pow(2, 6 * (t - 1)) * Math.Abs(Math.Sin(t * Math.PI * 3.5));
        }

        public static double EaseOutBounce(double t)
        {
            return 1 - Math.Pow(2, -6 * t) * Math.Abs(Math.Cos(t * Math.PI * 3.5));
        }

        public static double EaseInOutBounce(double t)
        {
            if (t < 0.5)
            {
                return 8 * Math.Pow(2, 8 * (t - 1)) * Math.Abs(Math.Sin(t * Math.PI * 7));
            }
            else
            {
                return 1 - 8 * Math.Pow(2, -8 * t) * Math.Abs(Math.Sin(t * Math.PI * 7));
            }
        }


        public delegate double Function(double t);

        /// <summary>
        /// Returns the function associated to the easingFunction enum. This value returned should be cached as it allocates memory
        /// to return.
        /// </summary>
        /// <param name="easingFunction">The enum associated with the easing function.</param>
        /// <returns>The easing function</returns>
        public static Function GetEasingFunction(Ease easingFunction)
        {
            if (easingFunction == Ease.EaseInQuad)
            {
                return EaseInQuad;
            }

            if (easingFunction == Ease.EaseOutQuad)
            {
                return EaseOutQuad;
            }

            if (easingFunction == Ease.EaseInOutQuad)
            {
                return EaseInOutQuad;
            }

            if (easingFunction == Ease.EaseInCubic)
            {
                return EaseInCubic;
            }

            if (easingFunction == Ease.EaseOutCubic)
            {
                return EaseOutCubic;
            }

            if (easingFunction == Ease.EaseInOutCubic)
            {
                return EaseInOutCubic;
            }

            if (easingFunction == Ease.EaseInQuart)
            {
                return EaseInQuart;
            }

            if (easingFunction == Ease.EaseOutQuart)
            {
                return EaseOutQuart;
            }

            if (easingFunction == Ease.EaseInOutQuart)
            {
                return EaseInOutQuart;
            }

            if (easingFunction == Ease.EaseInQuint)
            {
                return EaseInQuint;
            }

            if (easingFunction == Ease.EaseOutQuint)
            {
                return EaseOutQuint;
            }

            if (easingFunction == Ease.EaseInOutQuint)
            {
                return EaseInOutQuint;
            }

            if (easingFunction == Ease.EaseInSine)
            {
                return EaseInSine;
            }

            if (easingFunction == Ease.EaseOutSine)
            {
                return EaseOutSine;
            }

            if (easingFunction == Ease.EaseInOutSine)
            {
                return EaseInOutSine;
            }

            if (easingFunction == Ease.EaseInExpo)
            {
                return EaseInExpo;
            }

            if (easingFunction == Ease.EaseOutExpo)
            {
                return EaseOutExpo;
            }

            if (easingFunction == Ease.EaseInOutExpo)
            {
                return EaseInOutExpo;
            }

            if (easingFunction == Ease.EaseInCirc)
            {
                return EaseInCirc;
            }

            if (easingFunction == Ease.EaseOutCirc)
            {
                return EaseOutCirc;
            }

            if (easingFunction == Ease.EaseInOutCirc)
            {
                return EaseInOutCirc;
            }

            if (easingFunction == Ease.EaseInBounce)
            {
                return EaseInBounce;
            }

            if (easingFunction == Ease.EaseOutBounce)
            {
                return EaseOutBounce;
            }

            if (easingFunction == Ease.EaseInOutBounce)
            {
                return EaseInOutBounce;
            }

            if (easingFunction == Ease.EaseInBack)
            {
                return EaseInBack;
            }

            if (easingFunction == Ease.EaseOutBack)
            {
                return EaseOutBack;
            }

            if (easingFunction == Ease.EaseInOutBack)
            {
                return EaseInOutBack;
            }

            if (easingFunction == Ease.EaseInElastic)
            {
                return EaseInElastic;
            }

            if (easingFunction == Ease.EaseOutElastic)
            {
                return EaseOutElastic;
            }

            if (easingFunction == Ease.EaseInOutElastic)
            {
                return EaseInOutElastic;
            }

            return null;
        }


    }
}
