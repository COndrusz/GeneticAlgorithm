import re
import graphviz
import os
from PIL import Image


def read_output_file(file_path):
    """
    Reads and parses the output file to extract the input vector, performance, recovery, and grade.

    Parameters:
    file_path (str): The path to the output file.

    Returns:
    tuple: A tuple containing the input vector (list of ints), performance (float), recovery (float), and grade (float).

    Raises:
    ValueError: If the length of the input vector is not of the form 3n + 1.
    """
    with open(file_path, "r") as file:
        content = file.read()

    vector = list(map(int, re.findall(r"Input vector: (.+)", content)[0].split()))
    performance = float(re.findall(r"Performance: ([\d\.]+)", content)[0])
    recovery = float(re.findall(r"Recovery: ([\d\.]+)", content)[0])
    grade = float(re.findall(r"Grade: ([\d\.]+)", content)[0])

    if len(vector) % 3 != 1:
        raise ValueError("The input vector length must be of the form 3n + 1.")

    return vector, performance, recovery, grade


def create_graph(
    vector,
    performance,
    recovery,
    grade,
    edges,
    highlight_edge=None,
    highlight_node=None,
    show_labels=False,
):
    """
    Creates a graph visualization of the input vector and returns it as a Graphviz Digraph object.

    Parameters:
    vector (list of int): The input vector representing the connections in the circuit.
    performance (float): The performance metric of the circuit.
    recovery (float): The recovery metric of the circuit.
    grade (float): The grade metric of the circuit.
    edges (list of tuple): A list of edges to be added to the graph.
    highlight_edge (tuple, optional): The edge to be highlighted. Default is None.
    highlight_node (int, optional): The node to be highlighted. Default is None.
    show_labels (bool, optional): Whether to show performance, recovery, and grade labels. Default is False.

    Returns:
    graphviz.Digraph: The created graph.
    """
    # Calculate the number of nodes
    n = len(vector) // 3 - 1

    # Create a new Digraph
    dot = graphviz.Digraph()

    # Set the graph to left to right layout with optimized spacing
    dot.attr(rankdir="LR", nodesep="0.5", ranksep="1")

    # Define node names and properties
    node_names = {0: "Unit 0"}
    for i in range(1, n + 1):
        node_names[i] = f"Unit {i}"
    node_names[n + 1] = "Concentrate"
    node_names[n + 2] = "Tailings"

    # Add subgraph for the leftmost rank (feed node)
    with dot.subgraph() as s:
        s.attr(rank="same")
        s.node(
            "feed",
            "Feed",
            shape="box",
            style="filled",
            color="yellow",
            fontsize="24",
            fontname="Arial",
            width="2",
            height="1.5",
        )

    # Add nodes and edges based on the current step
    added_nodes = set()
    for edge in edges:
        source, target, color, port = edge
        if source not in added_nodes:
            source_color = "green" if source == highlight_node else "lightblue"
            if source in node_names:
                dot.node(
                    str(source),
                    node_names[source],
                    shape="box",
                    style="filled",
                    color=source_color,
                    fontsize="24",
                    fontname="Arial",
                    width="1.5",
                    height="1.2",
                )
            added_nodes.add(source)
        if target not in added_nodes:
            if target == n + 1:
                target_color = "lightgreen"  # Concentrate
            elif target == n + 2:
                target_color = "lightgrey"  # Tailings
            else:
                target_color = "green" if target == highlight_node else "lightblue"
            if target in node_names:
                dot.node(
                    str(target),
                    node_names[target],
                    shape="box",
                    style="filled",
                    color=target_color,
                    fontsize="24",
                    fontname="Arial",
                    width="1.5",
                    height="1.2",
                )
            else:
                # For intermediate nodes not in node_names
                dot.node(
                    str(target),
                    shape="box",
                    style="filled",
                    color=target_color,
                    fontsize="24",
                    fontname="Arial",
                    width="1.5",
                    height="1.2",
                )
            added_nodes.add(target)
        edge_color = "green" if edge == highlight_edge else color
        penwidth = "2" if edge != highlight_edge else "5"
        dot.edge(
            f"{source}:{port}",
            f"{target}:w",
            color=edge_color,
            penwidth=penwidth,
            style="solid",
        )

    # Add performance, recovery, and grade as labels in the last frame
    if show_labels:
        label_text = f"Vector: {vector}\nPerformance: {performance}\nRecovery: {recovery}\nGrade: {grade}"
        dot.attr(
            label=label_text,
            fontsize="40",
            labelloc="b",
            fontname="Arial",
            margin="0.5",
        )

    return dot


def create_animation(vector, performance, recovery, grade, output_dir):
    """
    Creates an animated GIF of the circuit diagram showing the step-by-step addition of edges.

    Parameters:
    vector (list of int): The input vector representing the connections in the circuit.
    performance (float): The performance metric of the circuit.
    recovery (float): The recovery metric of the circuit.
    grade (float): The grade metric of the circuit.
    output_dir (str): The directory where the output GIF file will be saved.

    Returns:
    str: The path to the saved GIF file.
    """
    steps_dir = os.path.join(output_dir, "steps")
    if not os.path.exists(steps_dir):
        os.makedirs(steps_dir)

    images = []
    steps = len(vector) // 3 * 3  # Total steps needed for the animation

    # Initial setup: first edge from feed
    edges = []
    edges.append(("feed", f"{vector[0]}", "black", "w"))

    visited = set()
    to_process = [vector[0]]
    edge_colors = ["blue", "purple", "red"]
    edge_ports = ["n", "e", "s"]

    while to_process:
        node = to_process.pop(0)
        if node in visited or node >= len(vector) // 3:
            continue
        visited.add(node)
        for i in range(3):
            target = vector[3 * node + 1 + i]
            if target >= len(vector) // 3 + 2:  # Skip invalid targets
                continue
            color = edge_colors[i % 3]
            port = edge_ports[i % 3]
            edges.append((node, target, color, port))
            if target not in visited and target < len(vector) // 3:
                to_process.append(target)

    for step in range(len(edges) + 1):
        show_labels = step == len(edges)  # Show labels only in the last frame
        current_edges = edges[:step]
        highlight_edge = edges[step - 1] if step > 0 else None
        highlight_node = highlight_edge[1] if highlight_edge else None
        dot = create_graph(
            vector,
            performance,
            recovery,
            grade,
            current_edges,
            highlight_edge,
            highlight_node,
            show_labels,
        )
        file_path = os.path.join(steps_dir, f"step_{step}.png")
        dot.render(file_path, format="png")
        images.append(Image.open(f"{file_path}.png").convert("RGBA"))

    # Ensure all images have the same shape
    widths, heights = zip(*(i.size for i in images))
    max_width = max(widths)
    max_height = max(heights)

    resized_images = []
    for img in images:
        new_img = Image.new("RGBA", (max_width, max_height), "white")
        new_img.paste(img, (0, 0), img)
        resized_images.append(new_img)

    # Create the animation
    gif_path = os.path.join(output_dir, "circuit_animation.gif")
    durations = [2000] * len(edges) + [
        15000
    ]  # Longer duration for each step and a long wait at the end
    resized_images[0].save(
        gif_path,
        save_all=True,
        append_images=resized_images[1:],
        duration=durations,
        loop=0,
        disposal=2,
    )
    return gif_path


if __name__ == "__main__":
    # Example usage
    file_path = "output.txt"
    output_dir = "./animations"
    vector, performance, recovery, grade = read_output_file(file_path)
    gif_path = create_animation(vector, performance, recovery, grade, output_dir)
    print(f"Animation saved to {gif_path}")
