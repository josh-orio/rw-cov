import matplotlib.pyplot as plt

fig, axes = plt.subplots(1, 2, figsize=(12, 6))

# time-series plot
axes[0].plot(vp_x, vp_y1)
axes[0].plot(vp_x, vp_y2)
axes[0].set_title(vp_title)
axes[0].set_xlabel(vp_xlabel)
axes[0].set_ylabel(vp_ylabel)
axes[0].grid(True)

# covariance plot
axes[1].plot(cp_x, cp_y)
axes[1].axhline(0, linestyle='--', color='black')
axes[1].set_title(cp_title)
axes[1].set_xlabel(cp_xlabel)
axes[1].set_ylabel(cp_ylabel)
axes[1].grid(True)

# figure - main title
fig.suptitle(main_title, fontsize=14)

# adjust layout to prevent overlap
plt.tight_layout(rect=[0, 0, 1, 0.95])

# save/show
# plt.show()
plt.savefig('graphs/side_by_side.png', dpi=128)
