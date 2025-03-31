import matplotlib.pyplot as plt

fig, ax1 = plt.subplots(figsize=(12, 6))

# time-series plot
ax1.plot(vp_x, vp_y1, label="sin(x)", color='black')
ax1.plot(vp_x, vp_y2, label="sin(x)", color='black')
ax1.set_ylabel(vp_ylabel)
ax1.set_xlabel(vp_xlabel)
ax1.grid(True)

# covariance plot
ax2 = ax1.twinx()
ax2.plot(cp_x, cp_y, color='r')
ax2.axhline(0, color='r', linestyle='--')
ax2.set_ylabel(cp_ylabel, color='r')

# figure - main title
plt.title(main_title)
fig.tight_layout()

# save/show
# plt.show()
plt.savefig('graphs/overlapped.png', dpi=128)
