import numpy as np
import random
import matplotlib.pyplot as plt

def generate_cities(n_cities, seed=42):
    np.random.seed(seed)
    return {i: (np.random.rand(), np.random.rand()) for i in range(n_cities)}

def calculate_distance_matrix(coords):
    cities = list(coords.keys())
    n = len(cities)
    matrix = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            x1, y1 = coords[i]
            x2, y2 = coords[j]
            matrix[i][j] = np.sqrt((x1-x2)**2 + (y1-y2)**2)
    return matrix

# 计算路径总距离
def calculate_path_distance(path, distance_matrix):
    """计算路径总距离，包括回到起点"""
    total = 0
    for i in range(len(path)-1):
        total += distance_matrix[path[i]][path[i+1]]
    # 添加回到起点的距离
    total += distance_matrix[path[-1]][path[0]]
    return total

# 2-opt局部搜索算法
def local_search(route, distance_matrix, max_iterations=20):
    """使用2-opt算法进行局部搜索优化"""
    best_route = route.copy()
    improved = True
    n = len(route)
    
    while improved and max_iterations > 0:
        improved = False
        max_iterations -= 1
        for i in range(1, n-1):
            for j in range(i+1, n):
                if j-i == 1: continue  # 相邻城市不交换
                new_route = best_route.copy()
                # 2-opt交换：翻转i到j之间的路径
                new_route[i:j] = new_route[i:j][::-1]
                
                # 计算新路径长度
                old_distance = calculate_path_distance(best_route, distance_matrix)
                new_distance = calculate_path_distance(new_route, distance_matrix)
                
                if new_distance < old_distance:
                    best_route = new_route
                    improved = True
                    break
            if improved:
                break
                    
    return best_route

def plot_route(best_tour, coords, title="Best Route"):
    plt.figure(figsize=(10, 6))
    x = [coords[city][0] for city in best_tour]
    y = [coords[city][1] for city in best_tour]
    
    x += [x[0]]
    y += [y[0]]
    
    plt.plot(x, y, 'o-', markersize=8, linewidth=1.5)
    plt.scatter(x, y, c='red', s=100)
    
    for i, city in enumerate(best_tour):
        plt.annotate(f"{city}", (coords[city][0], coords[city][1]),
                     fontsize=10, ha='center', va='bottom',
                     bbox=dict(boxstyle='round,pad=0.2', fc='white', ec='gray'))
    
    plt.title(title)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.axis('equal')
    plt.show()

class Particle:
    def __init__(self, cities):
        self.position = random.sample(cities, len(cities))
        self.velocity = []
        self.pbest = self.position.copy()
        self.fitness = self.calculate_fitness()
        self.best_fitness = self.fitness
    
    def calculate_fitness(self):
        total = 0
        for i in range(len(self.position)-1):
            total += distance_matrix[self.position[i]][self.position[i+1]]
        # 添加回到起点的距离
        total += distance_matrix[self.position[-1]][self.position[0]]
        return total
    
    def update_velocity(self, gbest, c1, c2, omega):
        new_velocity = []
        # 保留部分历史速度，使用omega参数控制
        new_velocity += [swap for swap in self.velocity if random.random() < omega]
        
        # 个体认知项
        if random.random() < c1:
            for i in range(len(self.position)):
                if self.position[i] != self.pbest[i] and random.random() < 0.3:
                    j = self.pbest.index(self.position[i])
                    new_velocity.append((i, j))
        
        # 社会认知项
        if random.random() < c2:
            for i in range(len(self.position)):
                if self.position[i] != gbest[i] and random.random() < 0.3:
                    j = gbest.index(self.position[i])
                    new_velocity.append((i, j))
        
        if random.random() < 0.1:  # 小概率添加随机交换
            i, j = random.sample(range(len(self.position)), 2)
            new_velocity.append((i, j))
            
        self.velocity = new_velocity
    
    def update_position(self):
        new_pos = self.position.copy()
        for i, j in self.velocity:
            new_pos[i], new_pos[j] = new_pos[j], new_pos[i]
        self.position = new_pos
        
    def apply_local_search(self, probability=0.1):
        if random.random() < probability:
            self.position = local_search(self.position, distance_matrix)

def pso_tsp(max_iter, num_particles, c1=2, c2=2, omega_start=0.9, omega_end=0.4, local_search_prob=0.1):
    global distance_matrix
    cities = list(range(len(distance_matrix)))
    particles = [Particle(cities) for _ in range(num_particles)]
    
    # 初始化全局最优
    gbest_particle = min(particles, key=lambda p: p.fitness)
    gbest = gbest_particle.position.copy()
    best_fitness = gbest_particle.fitness
    
    convergence = [best_fitness]
    no_improvement_count = 0
    last_best_fitness = best_fitness
    
    for iteration in range(max_iter):
        # 非线性惯性权重衰减
        omega = omega_start - (omega_start - omega_end) * (iteration / max_iter) ** 2
        
        for particle in particles:
            # 更新速度和位置
            particle.update_velocity(gbest, c1, c2, omega)
            particle.update_position()
            
            # 应用局部搜索
            particle.apply_local_search(local_search_prob)
            
            # 更新适应度
            current_fitness = particle.calculate_fitness()
            if current_fitness < particle.best_fitness:
                particle.pbest = particle.position.copy()
                particle.best_fitness = current_fitness
                
                if current_fitness < best_fitness:
                    best_fitness = current_fitness
                    gbest = particle.position.copy()
        
        # 记录收敛信息
        convergence.append(best_fitness)
        
        # 检查是否有改进
        if abs(best_fitness - last_best_fitness) < 1e-6:
            no_improvement_count += 1
        else:
            no_improvement_count = 0
        
        last_best_fitness = best_fitness
        
        # 如果连续多次没有改进，重新初始化部分粒子
        if no_improvement_count > 20:
            print(f"Iteration {iteration+1}: Restarting some particles...")
            for i in range(num_particles // 3):  # 重新初始化1/3的粒子
                particles[i] = Particle(cities)
            no_improvement_count = 0
        
        # 每隔一定迭代次数对全局最优解应用局部搜索
        if iteration % 10 == 0:
            gbest = local_search(gbest, distance_matrix)
            new_fitness = calculate_path_distance(gbest, distance_matrix)
            if new_fitness < best_fitness:
                best_fitness = new_fitness
                print(f"Iteration {iteration+1}: Improved by local search: {best_fitness:.2f}")
        
        print(f"Iteration {iteration+1}/{max_iter}, Best Fitness: {best_fitness:.4f}")
    
    # 最终对全局最优解应用一次局部搜索
    gbest = local_search(gbest, distance_matrix, max_iterations=50)
    final_fitness = calculate_path_distance(gbest, distance_matrix)
    if final_fitness < best_fitness:
        best_fitness = final_fitness
        print(f"Final optimization: {best_fitness:.4f}")
    
    # 绘制收敛曲线
    plt.figure(figsize=(10, 6))
    plt.plot(range(len(convergence)), convergence, 'b-', linewidth=2)
    plt.title('PSO Convergence Curve')
    plt.xlabel('Iteration')
    plt.ylabel('Best Fitness')
    plt.grid(True)
    plt.show()
    
    return gbest, best_fitness

# 主程序
if __name__ == "__main__":
    # 生成城市数据
    n_cities = 10 
    coords = generate_cities(n_cities)
    distance_matrix = calculate_distance_matrix(coords)
    
    # PSO参数设置
    max_iter = 200
    num_particles = 150  # 增加粒子数量
    
    # 运行PSO
    best_path, best_distance = pso_tsp(
        max_iter=max_iter,
        num_particles=num_particles,
        c1=1.49618,
        c2=1.49618,
        omega_start=0.9,
        omega_end=0.4,
        local_search_prob=0.1
    )
    
    print(f"最终路径长度: {best_distance:.4f}")
    
    # 可视化结果
    plot_route(best_path, coords, title=f"PSO TSP Solution (N={n_cities}, Distance={best_distance:.4f})")