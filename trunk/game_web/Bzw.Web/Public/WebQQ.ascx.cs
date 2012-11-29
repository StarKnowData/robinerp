using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Xml;
using System.IO;
using System.Net;

namespace Bzw.Web.Public
{
    public partial class WebQQ : System.Web.UI.UserControl
    {
        protected string contactStr = string.Empty;
        protected string AddStr = string.Empty;

        /// <summary>
        /// load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            //string urlfrom = "otherurl";
            //if (Request.UrlReferrer != null)
            //    urlfrom = Request.UrlReferrer.ToString();
            ////urlfrom = "http://www.baidu.com/s?wd=²´ÖÚ&amp;rsv_bp=0&amp;rsv_spt=3&amp;rsv_sug3=12&amp;rsv_sug=0&amp;rsv_sug1=9&amp;rsv_sug4=10862&amp;inputT=10231";
            string xmlPath = Server.MapPath("/Upload/Xml/WebQQ.config");
            XmlDocument xml = new XmlDocument();
            /////把页面来源保存在cookies里
            //if (BzwCache.Default.Get<CookiesCache>("urlfrom")!=null)
            //    BzwCache.Default.Delete<CookiesCache>("urlfrom");
            //BzwCache.Default.Save<CookiesCache>("urlfrom",urlfrom);

            if (File.Exists(xmlPath))
            {
                DataSet ds = new DataSet();
                ds.ReadXml(xmlPath);
                DataTable dt = ds.Tables[0];

                if (dt.Rows.Count > 0)
                {

                    string[] str = new string[dt.Rows.Count];
                    List<string> list = new List<string>();
                    for (int i = 0; i < dt.Rows.Count; i++)
                    {
                        //str[i] = "<li><span style='float:left;'><a href='javascript:' onclick=\"QQHit(" + dt.Rows[i]["number"] + ")\" ><img src='" + (QQUtility.IsOnline(dt.Rows[i]["number"].ToString()) == true ? "/Images/pop_bullet01.gif" : "/Images/pop_bullet02.gif") + "'/>&nbsp;</a></span><span style='float:right; padding-right:20px;'><a href='javascript:' onclick=\"QQHit(" + dt.Rows[i]["number"] + ")\">" + dt.Rows[i]["name"] + "</a></span></li>";
                        //str[i] = "<li><span style='float:left;'><a href='javascript:' onclick=\"QQHit(" + dt.Rows[i]["number"] + "," + urlfrom + ")\" ><img src='/Images/pop_bullet01.gif'/>&nbsp;</a></span><span style='float:right; padding-right:20px;'><a href='javascript:' onclick=\"QQHit(" + dt.Rows[i]["number"] + "," + urlfrom + ")\">" + dt.Rows[i]["name"] + "</a></span></li>";
                        str[i] = "<li><span style='float:left;'><a href='javascript:' onclick=\"QQHit(" + dt.Rows[i]["number"] + ")\" ><img src='" + (IsOnline(dt.Rows[i]["number"].ToString()) == true ? "/Images/pop_bullet01.gif" : "/Images/pop_bullet02.gif") + "'/>&nbsp;</a></span><span style='float:right; padding-right:20px;'><a href='javascript:' onclick=\"QQHit(" + dt.Rows[i]["number"] + ")\">" + dt.Rows[i]["name"] + "</a></span></li>";
                    }

                    //随机排列次序
                    str = Arrrandom(str);
                    int j = 0;
                    for (int i = 0; i < str.Length; i++)
                    {
                        try
                        {
                            if (str[i] != null)
                            {
                                j++;

                            }
                            if (j > dt.Rows.Count && str[i] != null)
                            {

                                AddStr += str[i].Replace("<li>", "<span  style='color:#fff;'>").Replace("</li>", "").Replace("<span style='color:#fff;'>", "");
                            }
                            else
                            {
                                contactStr += str[i];
                            }
                        }
                        catch
                        {

                        }
                    }
                    if (list.Count > 0)
                    {
                        foreach (string str0 in list)
                        {
                            AddStr += str0;
                        }
                    }
                }

            }
        }

        /// <summary>
        /// 将数组打乱重排
        /// </summary>
        /// <param name="arr">数组</param>
        /// <returns>重排后数组</returns>
        public string[] Arrrandom(string[] arr)
        {
            Random ran = new Random();
            int k = 0;
            string strtmp = "";
            for (int i = 0; i < arr.Length; i++)
            {
                k = ran.Next(0, arr.Length);
                if (k != i)
                {
                    strtmp = arr[i];
                    arr[i] = arr[k];
                    arr[k] = strtmp;
                }
            }
            return arr;
        }

        public static bool IsOnline(string qq)
        {
            WebClient client = new WebClient();
            byte[] data;
            try { data = client.DownloadData("http://wpa.qq.com/pa?p=1:" + qq.ToString() + ":1"); }
            catch { data = new byte[0]; }
            switch (data.Length)
            {
                case 2329:
                    return true;//在线

                case 2262:
                    return false;//不在线

                case 0:
                    return false;//不存在

                default:
                    return false;

            }

        } 
    }
}