/*
	Manages all keybinds for COM
*/
class COMKeyBinds extends Module 
{
	bool m_IsHudVisible = true;
	
	void COMKeyBinds()
	{
	}

	void ~COMKeyBinds()
	{
	}
	
	override void Init() 
	{
		super.Init();
	}
	
	override void onUpdate( int timeslice )
	{
	}
	
	override void RegisterKeyMouseBindings() 
	{
		KeyMouseBinding toggleCursor = new KeyMouseBinding( GetModuleType() , "ToggleCursor"  , "[U]"    , "Toggles the cursor."   , true);
		KeyMouseBinding toggleUI     = new KeyMouseBinding( GetModuleType() , "ToggleUI"      , "[HOME]" , "Toggles the UI."       );
		KeyMouseBinding teleport	 = new KeyMouseBinding( GetModuleType() , "TeleportCursor", "[T]"    , "Teleport to cursor position." );
		KeyMouseBinding reload       = new KeyMouseBinding( GetModuleType() , "Reload"        , "[R]"    , "Instantly reloads mag.");

		toggleCursor.AddKeyBind( KeyCode.KC_U,    KeyMouseBinding.KB_EVENT_PRESS );
		toggleUI    .AddKeyBind( KeyCode.KC_HOME, KeyMouseBinding.KB_EVENT_RELEASE );
		teleport    .AddKeyBind( KeyCode.KC_T,    KeyMouseBinding.KB_EVENT_PRESS   );
		reload      .AddKeyBind( KeyCode.KC_R,    KeyMouseBinding.KB_EVENT_RELEASE );
		
		RegisterKeyMouseBinding( toggleCursor );
		RegisterKeyMouseBinding( toggleUI );
		RegisterKeyMouseBinding( teleport );
		RegisterKeyMouseBinding( reload );
	}

    void ToggleCursor()
    {
        if ( GetGame().GetInput().HasGameFocus( INPUT_DEVICE_MOUSE ) )
        {
            GetGame().GetInput().ChangeGameFocus( 1, INPUT_DEVICE_MOUSE );
            GetGame().GetUIManager().ShowUICursor( true );
        }
        else
        {
            GetGame().GetUIManager().ShowUICursor( false );
            GetGame().GetInput().ResetGameFocus( INPUT_DEVICE_MOUSE );
        }
    }

    void ToggleUI()
    {
        GetGame().GetUIManager().ShowScriptedMenu( new EditorMenu , NULL );
        //m_IsHudVisible = !m_IsHudVisible;
        //GetGame().GetMission().GetHud().Show(m_IsHudVisible);

    }

    void TeleportCursor()
    {
        Print( "COMKeyBinds::TeleportCursor()" );

//		if ( CameraTool.Cast( m_Mission.GetModule( CameraTool ) ).IsUsingCamera() ) //Todo renable after module manager is done
//		{
//			GetPlayer().MessageStatus( "You can not teleport while you are inside the freecam!" );
//			return;
//		}

        
        vector hitPos = GetCursorPos();

        float distance = vector.Distance( GetPlayer().GetPosition(), hitPos );

        if ( distance < 5000 )
        {
            EntityAI oVehicle = GetPlayer().GetDrivingVehicle();

            if( oVehicle )
            {
                GetPlayer().MessageStatus( "Get out of the vehicle first!" );
            }
            else
            {
                GetPlayer().SetPosition( hitPos );
                GetPlayer().MessageStatus( "Teleported!" );
            }
        }
        else
        {
            GetPlayer().MessageStatus( "Distance for teleportation is too far!" );
        }
    }

    void Reload()
    {
        EntityAI oWeapon = GetPlayer().GetHumanInventory().GetEntityInHands();

        if( oWeapon )
        {
            Magazine oMag = ( Magazine ) oWeapon.GetAttachmentByConfigTypeName( "DefaultMagazine" );

            if( oMag && oMag.IsMagazine() )
            {
                oMag.LocalSetAmmoMax();
            }

            Object oSupressor = ( Object ) oWeapon.GetAttachmentByConfigTypeName( "SuppressorBase" );

            if( oSupressor )
            {
                oSupressor.SetHealth( oSupressor.GetMaxHealth( "", "" ) );
            }
        }
    }


}