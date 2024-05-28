from discord_webhook import DiscordWebhook, DiscordEmbed

webhook = DiscordWebhook(url="https://discord.com/api/webhooks/1186979233696854046/kGgrw3__1UhXbGDFZvJkFKraWi2Ca9HiF-S7YuWNuGUAH9YDZY5XbG_PdgVTiVJU9Gxw")

# create embed object for webhook
# you can set the color as a decimal (color=242424) or hex (color="03b2f8") number
embed = DiscordEmbed(title="Manual activated", description="pump : open ,fan : open", color="03b2f8")

# add embed object to webhook
webhook.add_embed(embed)

response = webhook.execute()