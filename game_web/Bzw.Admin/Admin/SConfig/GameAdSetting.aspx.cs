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
using Bzw.Data;
using System.IO;
using System.Xml;

public partial class Admin_SConfig_GameAdSetting :AdminBasePage
{
    public int TableID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("01");


		string xmlPath = Server.MapPath( "/Upload/xml/GameAD.xml" );
        if (!File.Exists(xmlPath))
        {//如果不存在就创建该文件
			XmlDocument xml = new XmlDocument();
			xml.LoadXml("<?xml version=\"1.0\" encoding=\"utf-8\"?><bcaster></bcaster>");//创建xml文件头部
			XmlElement xmlRoot = xml.DocumentElement;//获取根元素

			for (int i = 1; i <= 7; i++) //初始化7个广告位
			{
				XmlElement xmlSon = xml.CreateElement("item");
				XmlAttribute xmlattr = xml.CreateAttribute("id");
				xmlattr.Value = i.ToString();
				xmlSon.Attributes.Append(xmlattr);
				XmlElement title = xml.CreateElement("title");
				title.InnerText = "游戏广告位" + i.ToString();
				xmlSon.AppendChild(title);
				XmlElement content = xml.CreateElement("Content");
				content.InnerText = "";
				xmlSon.AppendChild(content);
				xmlRoot.AppendChild(xmlSon);
				
			}
			xml.Save(xmlPath);

           // return;
        }

        DataSet ds = new DataSet();
        ds.ReadXml(xmlPath);
        if (ds.Tables.Count > 0)
        {
            DataTable sd = ds.Tables[0];
            if (sd.Rows.Count > 0)
            {
                FlashAdlist.DataSource = sd;
                FlashAdlist.DataBind();
            }
            sd.Clear();
        }
        else
            return;

    }
}
