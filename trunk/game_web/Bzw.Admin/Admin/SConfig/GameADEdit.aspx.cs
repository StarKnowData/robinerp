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
using BCST.Common;
using System.Xml;
using System.IO;

public partial class Admin_SConfig_GameADEdit : AdminBasePage
{

    protected string title = string.Empty;
    protected string AdId
    {
        get {
            string temp = CommonManager.Web.Request("id", "");
            if(!string.IsNullOrEmpty(temp))
            {
            return temp;
            
            }
            return
                "0";
        
        }

    
    
    }
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("01");
        if (!IsPostBack)
        {
            XmlDocument xml = new XmlDocument();
            string xmlPath = Server.MapPath("/Upload/xml/GameAD.xml");
            if (!File.Exists(xmlPath))
            {
                return;
            }
            xml.Load(xmlPath);
            XmlNode node = xml.SelectSingleNode("//item[@id='" + AdId + "']");
            title = node["title"].InnerText;
            content.Value = node["Content"].InnerText;
        }
    }

    protected void GameADEd(object sender, EventArgs e)
    {
        XmlDocument xml = new XmlDocument();
        try
        {
			string xmlPath = Server.MapPath( "/Upload/xml/GameAD.xml" );
            if (!File.Exists(xmlPath))
            {
                return;
            }
            xml.Load(xmlPath);

            XmlNode node = xml.SelectSingleNode("//item[@id='" + AdId + "']");

            //node.RemoveChild(node.ChildNodes[1]);//先将整个子节点删除
            //XmlElement xmelem = xml.CreateElement("Content");
            //XmlCDataSection cdata = xml.CreateCDataSection(content.Value);
            //xmelem.AppendChild(cdata);
            //node.AppendChild(xmelem);
            node["Content"].InnerText = "";
            XmlCDataSection cdata = xml.CreateCDataSection(content.Value);
            node.ChildNodes[1].AppendChild(cdata);

        
            xml.Save(xmlPath);
            CommonManager.Web.RegJs(this, "alert('修改成功！');location.href='gameadsetting.aspx';", false);
        }
        catch(Exception ex) {
            
            CommonManager.Web.RegJs(this, "alert(\"修改失败！"+ex.Message.Substring(0,39)+"\");location.href=location.href;", false);
        }
    
    }
}
