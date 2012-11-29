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
using Bzw.Data;
using System.Xml;

public partial class Admin_FlashAd_FlashDel : AdminBasePage
{
	string FlashID;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "01" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');history.back();", false );
			return;
		}
		else
			FlashID = tmp;//Limit.editCharacter(Limit.getFormValue("id"));

        string xmlPath = Server.MapPath("/upload/xml/flash.xml");
        if (!System.IO.File.Exists(xmlPath))
        {
            CommonManager.Web.RegJs(this, "alert('幻灯片删除失败，flash.xml文件不存在！');history.back();", false);
        
        }

        try
        {
            XmlDocument xml = new XmlDocument();
            xml.Load(xmlPath);
            //XmlElement root = xml.DocumentElement;

            XmlNode node = xml.SelectSingleNode("//item[@id='" + FlashID + "']");
           
            XmlNode parent = node.ParentNode;
            parent.RemoveChild(node);
            xml.Save(xmlPath);

            Response.Write("<script>alert('幻灯片删除成功！');location.href='FlashAd.aspx';</script>");
        }
        catch(Exception ex)
        {
            Response.Write("<script>alert('幻灯片删除失败！"+ex.Message+"');location.href='FlashAd.aspx';</script>");
        
        }




	
	}
}
