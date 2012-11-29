using System;
using System.Configuration;
using System.Web.Configuration;
using BCST.Common;

public partial class Admin_UserAdmin_ConfigEncryption : AdminBasePage
{

	public Configuration config;
	public ConfigurationSection connnetStrings;
	public bool IsEncry;
	protected void Page_Load( object sender, EventArgs e )
	{
        AdminPopedom.IsHoldModel(string.Empty);
		config = WebConfigurationManager.OpenWebConfiguration( Request.ApplicationPath );
		connnetStrings = config.GetSection( "connectionStrings" );
		IsEncry = connnetStrings.SectionInformation.IsProtected;	
	}

	private Configuration getConfig()
	{
		return WebConfigurationManager.OpenWebConfiguration( Request.ApplicationPath );
	}

	protected void Button1_Click( object sender, EventArgs e )
	{
		if( connnetStrings != null )
		{
			if( !IsEncry )
			{
				connnetStrings.SectionInformation.ProtectSection( "DataProtectionConfigurationProvider" );
				config.Save();
				CommonManager.Web.RegJs( this.Page, "alert('加密成功！');location.href=location.href;", true );
			}
			CommonManager.Web.RegJs( this.Page, "alert('已经加过密了！');", true );
		}
	}
	protected void Button2_Click( object sender, EventArgs e )
	{
		if( connnetStrings != null )
		{
			if( IsEncry )
			{
				connnetStrings.SectionInformation.UnprotectSection();
				config.Save();
				CommonManager.Web.RegJs( this.Page, "alert('解密成功！');location.href=location.href;", true );
			}
			CommonManager.Web.RegJs( this.Page, "alert('已经解过密了！');", true );
		}
	}
}
