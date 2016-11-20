package aits.geology.machines.anvil;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;

import net.minecraft.client.gui.GuiButton;
import net.minecraft.client.gui.inventory.GuiContainer;
import net.minecraft.entity.player.InventoryPlayer;
import net.minecraft.nbt.NBTTagCompound;
import net.minecraft.network.packet.Packet250CustomPayload;

import org.lwjgl.opengl.GL11;

import aits.core.common.CommonProxy;
import cpw.mods.fml.common.network.PacketDispatcher;

public class GuiAnvil extends GuiContainer
{
	TileAnvil TheAnvil;

	public GuiAnvil(InventoryPlayer inventoryPlayer, TileAnvil tileEntity)
	{
		super(new ContainerAnvil(inventoryPlayer, tileEntity));
		TheAnvil = tileEntity;
	}


	@Override
	public void initGui()
	{
		super.initGui();
		// make buttons
		// id, x, y, width, height, text
		int i = 0;
		for(int y = 19; y <= 59; y += 10)
		{
			for(int x = 29; x <= 119; x += 10)
			{
				buttonList.add(new GuiAnvilButton(i, this.guiLeft + x, this.guiTop + y, this));
				i++;
			}
		}
		buttonList.add(new GuiAnvilButton(50, this.guiLeft + 8, this.guiTop + 54, 16, 16, ""));

		NBTTagCompound tag = new NBTTagCompound();
		TheAnvil.writeToNBT(tag);
		TheAnvil.readFromNBT(tag);


		for(int z = 0; z < 50; z++)
		{
			((GuiAnvilButton) this.buttonList.get(z)).IsEnabled = !TheAnvil.GetButtonState()[z];
		}
	}

	@Override
	protected void actionPerformed(GuiButton guibutton)
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream(16);
		DataOutputStream output = new DataOutputStream(bos);

		if(guibutton.id < 50)
		{
			((GuiAnvilButton) buttonList.get(guibutton.id)).IsEnabled = !((GuiAnvilButton) buttonList.get(guibutton.id)).IsEnabled;
		}

		try
		{
			// Button ID
			output.writeInt(guibutton.id);

			// Coords
			output.writeInt(TheAnvil.xCoord);
			output.writeInt(TheAnvil.yCoord);
			output.writeInt(TheAnvil.zCoord);
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}

		Packet250CustomPayload packet = new Packet250CustomPayload();
		packet.channel = "AITSGeologyAnvil";
		packet.data = bos.toByteArray();
		packet.length = bos.size();

		PacketDispatcher.sendPacketToServer(packet); // send packet
	}

	@Override
	public void onGuiClosed()
	{
		super.onGuiClosed();
		TheAnvil.closeChest();
	}

	@Override
	protected void drawGuiContainerForegroundLayer(int param1, int param2)
	{
		// draw text and stuff here
		// the parameters for drawString are: string, x, y, color
		fontRenderer.drawString("Anvil", 8, 6, 4210752);
	}

	@Override
	protected void drawGuiContainerBackgroundLayer(float par1, int par2, int par3)
	{
		// draw your Gui here, only thing you need to change is the path
		GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
		mc.renderEngine.bindTexture(CommonProxy.EnumTextureList.AnvilGui.GetPath());
		int x = (width - xSize) / 2;
		int y = (height - ySize) / 2;
		this.drawTexturedModalRect(x, y, 0, 0, xSize, ySize);
	}
}
