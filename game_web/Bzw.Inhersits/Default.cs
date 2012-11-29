using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

namespace Bzw.Inhersits
{
	public partial class Default : UiCommon.BasePage
	{

		protected void Page_Load( object sender, EventArgs e )
		{
			//静态页面过期常量的KEY
			string Key_Default_Build = "Key_Default_Build";
			//动态页面Url
			string dongPageUrl = "/Default2.aspx";
			//静态页面Url
			string jingPageUrl = "/Default.html";
			//静态文件存放根目录
			string RootFilePath = "/Html";

			string returnPageUrl = new UiCommon.BuildStatic().PageBuild( Key_Default_Build, dongPageUrl, jingPageUrl, RootFilePath );
			Response.Redirect( returnPageUrl );


			/*
			//静态页面过期常量的KEY
			string Key_Default_Build = "Key_Default_Build";
			//动态页面文件名
			string dongPageUrl = "/Default.aspx";
			//静态页面文件名
			string jingPageUrl = "/Default.html";
			//静态文件存放根目录
			string RootFilePath = "/Html";

			//1.获取过期常量
			int timeOutCost = 0;
			if (ConfigurationManager.AppSettings[Key_Default_Build] != null)
			{
				string temp = ConfigurationManager.AppSettings[Key_Default_Build];
				if (BCST.Common.CommonManager.String.IsInteger(temp))
				{
					timeOutCost = Convert.ToInt32(temp);
				}
			}

			//2.如果常量小于或等于0，直接访问动态页面
			if (timeOutCost <= 0)
			{
				Response.Redirect(dongPageUrl);
			}

			//3.---------
			string path = HttpContext.Current.Server.MapPath(RootFilePath + jingPageUrl);
			DateTime fileLastWriteTime = new DateTime(1970, 1, 1, 8, 0, 0);
			if (File.Exists(path))//判断文件是否存在，存在则获取文件最后修改时间
			{
				fileLastWriteTime = File.GetLastWriteTime(path);
			}
			//文件最后修改时间加上过期常量，如小于当前时间，重新生成静态文件
			if (fileLastWriteTime.AddMinutes(timeOutCost) < DateTime.Now)
			{
				//生成静态页面
				System.Net.WebRequest rq = System.Net.WebRequest.Create("http://" + Request.ServerVariables["Http_Host"] + dongPageUrl);
				System.Net.HttpWebResponse rp = (System.Net.HttpWebResponse)rq.GetResponse();
				System.IO.Stream pageStream = rp.GetResponseStream();
				using (System.IO.StreamReader sr = new System.IO.StreamReader(pageStream))
				{
					System.IO.File.WriteAllText(path, sr.ReadToEnd(), System.Text.Encoding.UTF8);
				}
				rq.Abort();
				rp.Close();
				pageStream.Close();
			}

			//4.页面跳转
			if (File.Exists(path))
			{
				Response.Redirect(RootFilePath + jingPageUrl);
			}
			else
			{
				Response.Redirect(dongPageUrl);
			}
			*/
		}
	}
}
