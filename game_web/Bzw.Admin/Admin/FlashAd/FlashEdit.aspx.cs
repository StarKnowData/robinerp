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
using BCST.Common;
using Bzw.Data;
using System.Xml;

public partial class Admin_FlashAd_FlashEdit : AdminBasePage
{
	string FlashID;
	public string title=string.Empty, picture=string.Empty, url=string.Empty, flash_sort=string.Empty, through=string.Empty;
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
			FlashID = tmp;
        if (!IsPostBack)
        {
            xmlDatabind();
        
        }


           
	}

    private void xmlDatabind()
    {


        string xmlPath = Server.MapPath("/Upload/xml/flash.xml");
        if (!File.Exists(xmlPath))
        {
            return;

        }

        XmlDocument xml = new XmlDocument();
        xml.Load(xmlPath);

        string xp = "//item[@id='" + FlashID + "']";

        XmlElement xmlRoot = xml.DocumentElement;//取得文档的根节点
        XmlNode xn = xmlRoot.SelectSingleNode(xp);


        title = xn.Attributes["itemtitle"].Value;
        picture = xn.Attributes["item_url"].Value;
        url = xn.Attributes["link"].Value;

    
    }


	protected void FlashEdits( object sender, EventArgs e )
	{
		string flashImg = "";
		string title, url;
		title = CommonManager.Web.Request( "title", "" );
        //if( title.ToString() == "" )
        //{
        //    CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n标题不能为空！');", false);
        //    return;
        //}
		url = CommonManager.Web.Request( "url", "" );
		if( url.ToString() == "" )
		{
			CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\nUrl连接地址不能为空！');", false);
			return;
		}
	
		


		#region 上传图片
		if( FileUpload1.HasFile )
		{
			string fileContentType = FileUpload1.PostedFile.ContentType;
			if( fileContentType == "image/pjpeg" )//fileContentType == "image/bmp" || fileContentType == "image/gif" || 
			{

				string name = FileUpload1.PostedFile.FileName;                  // 客户端文件路径

				FileInfo file = new FileInfo( name );
				string fileName = file.Name;                                    // 文件名称
				String FileType = fileName.Substring( fileName.Length - 4, 4 );     //获的扩展名
				string photoName_New = DateTime.Now.Minute.ToString() + DateTime.Now.Second.ToString() + FileType;//用用户名和时间来重命名图片，以防重名  

				string webFilePath = Server.MapPath( "~/Upload/Flash/" + photoName_New );        // 服务器端文件路径

				if( !File.Exists( webFilePath ) )
				{
					try
					{
						FileUpload1.SaveAs( webFilePath );
						flashImg = "/Upload/Flash/" + photoName_New;
					}
					catch( Exception ex )
					{
						Response.Write( ex.Message );
						Response.End();
					}
				}
			}
			else
			{
				Page.ClientScript.RegisterStartupScript( this.GetType(), "Login", "<script>alert('图片格式必须为jpg格式！')</script>" );
				return;
			}
		}
		#endregion
		string xmlPath = Server.MapPath( "/Upload/xml/flash.xml" );
        if (!File.Exists(xmlPath))
        {
            return;

        }

        XmlDocument xml = new XmlDocument();
        xml.Load(xmlPath);

        string xp = "//item[@id='" + FlashID + "']";

        XmlElement xmlRoot = xml.DocumentElement;//取得文档的根节点
        XmlNode xn = xmlRoot.SelectSingleNode(xp);


        xn.Attributes["itemtitle"].Value=title;
        if (flashImg != "")
        {
            xn.Attributes["item_url"].Value = flashImg;
        }
        xn.Attributes["link"].Value=url;
        try
        {
            xml.Save(xmlPath);
            CommonManager.Web.RegJs(this, "alert('修改成功！')", false);
            xmlDatabind();
        }
        catch (Exception ex)
        {
            CommonManager.Web.RegJs(this, "alert('修改失败！"+ex.Message+"')", false);
        }

   
	}
}
