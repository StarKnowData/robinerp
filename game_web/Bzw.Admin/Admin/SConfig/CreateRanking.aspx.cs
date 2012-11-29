using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.IO;
using System.Text;

public partial class Admin_SConfig_CreateRanking : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("12");
    }

    protected void CreateHtml(object sender, EventArgs e)
    {
        try
        {

            //文件存放根目录
            string RootFilePath = "/Html/Ranking/";
            //域名
            string domain = Request.Url.OriginalString.ToLower().Replace("/admin/sconfig/createranking.aspx", ""); //System.Configuration.ConfigurationSettings.AppSettings["Domain"].TrimEnd( '/' );

            //Ranking.aspx
            System.Net.WebRequest rq = System.Net.WebRequest.Create(domain + "/Ranking2.aspx");
            System.Net.HttpWebResponse rp = (System.Net.HttpWebResponse)rq.GetResponse();
            System.IO.Stream pageStream = rp.GetResponseStream();
            using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
            {
                //读取
                string tmp = sr.ReadToEnd();
                //无参数的Ranking.html
                string path = HttpContext.Current.Server.MapPath(RootFilePath + "Ranking.html");
                using (System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false, System.Text.Encoding.UTF8))
                {
                    sw.Write(tmp);
                }
            }
            rq.Abort();
            rp.Close();
            pageStream.Close();

            //RankFascination.aspx
            rq = System.Net.WebRequest.Create(domain + "/RankFascination2.aspx");
            rp = (System.Net.HttpWebResponse)rq.GetResponse();
            pageStream = rp.GetResponseStream();
            using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
            {
                //读取
                string tmp = sr.ReadToEnd();
                //无参数的Ranking.html
                string path = HttpContext.Current.Server.MapPath(RootFilePath + "RankFascination.html");
                using (System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false, System.Text.Encoding.UTF8))
                {
                    sw.Write(tmp);
                }
            }
            rq.Abort();
            rp.Close();
            pageStream.Close();

            //RankGameTime.aspx
            rq = System.Net.WebRequest.Create(domain + "/RankGameTime2.aspx");
            rp = (System.Net.HttpWebResponse)rq.GetResponse();
            pageStream = rp.GetResponseStream();
            using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
            {
                //读取
                string tmp = sr.ReadToEnd();
                //无参数的Ranking.html
                string path = HttpContext.Current.Server.MapPath(RootFilePath + "RankGameTime.html");
                using (System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false, System.Text.Encoding.UTF8))
                {
                    sw.Write(tmp);
                }
            }
            rq.Abort();
            rp.Close();
            pageStream.Close();

            //RankMoney.aspx
            rq = System.Net.WebRequest.Create(domain + "/RankMoney2.aspx");
            rp = (System.Net.HttpWebResponse)rq.GetResponse();
            pageStream = rp.GetResponseStream();
            using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
            {
                //读取
                string tmp = sr.ReadToEnd();
                //无参数的Ranking.html
                string path = HttpContext.Current.Server.MapPath(RootFilePath + "RankMoney.html");
                using (System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false, System.Text.Encoding.UTF8))
                {
                    sw.Write(tmp);
                }
            }
            rq.Abort();
            rp.Close();
            pageStream.Close();

            //RankOnLineTime.aspx
            rq = System.Net.WebRequest.Create(domain + "/RankOnLineTime2.aspx");
            rp = (System.Net.HttpWebResponse)rq.GetResponse();
            pageStream = rp.GetResponseStream();
            using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
            {
                //读取
                string tmp = sr.ReadToEnd();
                //无参数的Ranking.html
                string path = HttpContext.Current.Server.MapPath(RootFilePath + "RankOnLineTime.html");
                using (System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false, System.Text.Encoding.UTF8))
                {
                    sw.Write(tmp);
                }
            }
            rq.Abort();
            rp.Close();
            pageStream.Close();

            //Ranking带参数的页面输出开始

            System.Data.DataTable dt;
            object dtCache = HttpContext.Current.Cache.Get("GameIDList"); //BCST.Cache.BCSTCache.Default.Get<BCST.Cache.AspNetCache>("GameIDList");
            if (dtCache == null)
            {
                //重新读取
                dt = new BLL.Game().ListTGameNameInfo(0);

                HttpContext.Current.Cache.Insert("GameIDList", dt, null, System.Web.Caching.Cache.NoAbsoluteExpiration, new TimeSpan(12, 0, 0));
            }
            else
            {
                dt = (System.Data.DataTable)dtCache;
            }

            foreach (System.Data.DataRow row in dt.Rows)
            {
                rq = System.Net.WebRequest.Create(domain + "/Ranking2.aspx?id=" + row["NameID"].ToString() + "&name=" + Server.UrlEncode(row["ComName"].ToString()));
                rp = (System.Net.HttpWebResponse)rq.GetResponse();
                pageStream = rp.GetResponseStream();
                using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
                {
                    //读取
                    string tmp = sr.ReadToEnd();
                    //无参数的Ranking.html
                    string path = HttpContext.Current.Server.MapPath(RootFilePath + "Ranking_" + row["NameID"].ToString() + ".html");
                    using (System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false, System.Text.Encoding.UTF8))
                    {
                        sw.Write(tmp);
                    }
                }
                rq.Abort();
                rp.Close();
                pageStream.Close();
            }
            msg.Text = "全部生成成功！"+DateTime.Now;
            msg.ForeColor = System.Drawing.Color.Green;
        }
        catch (Exception ex)
        {

            msg.Text = "生成失败："+ex.Message;

        
        }

    
    }
}
